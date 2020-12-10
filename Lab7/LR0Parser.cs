using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using lab2.LR0.Actions;
using lab2.LR0.Models;

namespace lab2.LR0
{
    public enum StateType
    {
        Shift,
        Reduce,
        Acc,
        Conflict
    }

    public class LR0Parser
    {
        private const bool IS_LOGGER_ACTOVE = false;

        private Grammar grammar;
        private AugmentedGrammar augmentedGrammar;
        private List<KeyValuePair<ClosureAction, LR0State>> calculatedStates = new List<KeyValuePair<ClosureAction, LR0State>>();
        private List<List<string>> table = new List<List<string>>();

        private void Log(object obj)
        {
            if (IS_LOGGER_ACTOVE)
                Console.WriteLine(obj.ToString());
        }

        public List<string> GetNonterminals()
        {
            return grammar.Nonterminals;
        }

        public List<string> GetTerminals()
        {
            return grammar.Terminals;
        }

        public Dictionary<string, List<string>> GetProductions()
        {
            return grammar.Productions;
        }

        public List<string> GetProductionsFor(string nonterminal)
        {
            if (grammar.Productions.ContainsKey(nonterminal))
                return grammar.Productions[nonterminal];
            return new List<string>();
        }


        public static LR0Parser FromFile(string filePath)
        {
            LR0Parser parser = null;

            var grammar = Grammar.FromFile(filePath);
            if (grammar != null)
            {
                var augmentedGrammar = AugmentedGrammar.Augement(grammar);
                parser = new LR0Parser()
                {
                    grammar = grammar,
                    augmentedGrammar = augmentedGrammar
                };
            }

            return parser;
        }

        private List<LR0Item> Closure(List<LR0Item> inputItems)
        {
            var closure = new List<LR0Item>();
            closure.AddRange(inputItems);

            var index = 0;
            var addedNonterminals = inputItems.Select(item => item.lhs).ToList();

            while (index < closure.Count())
            {
                var currentItem = closure[index];

                var nonterminal = currentItem.GetNonterminalAfterDot();

                if (nonterminal == null)
                {
                    index++;
                    continue;
                }

                foreach (var addedNonterminal in addedNonterminals)
                    if (addedNonterminal.Equals(nonterminal))
                    {
                        index++;
                        continue;
                    }

                if ((augmentedGrammar.Productions.ContainsKey(nonterminal)))
                {
                    addedNonterminals.Add(nonterminal);
                    closure.AddRange(augmentedGrammar.Productions[nonterminal]);
                }
                index ++;
            }

            return closure;
        }

        private KeyValuePair<LR0State, bool> Goto(LR0State state, string symbol)
        {
            LR0State resultState = null;
            var isNew = true;

            var inputItems = state.Items
                .Where(item =>
                    {
                        var itmeSymbol = item.GetSymbolAfterDot();
                        if (itmeSymbol == null)
                            return false;

                        return itmeSymbol.Equals(symbol);
                    })
                .ToList();

            var newItems = inputItems.Select(item => item.MoveDot()).ToList();

            if (newItems.Count != 0)
            {
                foreach (var calculatedState in calculatedStates)
                {
                    if (calculatedState.Key.Equals(new ClosureAction(newItems)))
                    {
                        resultState = calculatedState.Value;
                        isNew = false;
                    }
                }

                if (resultState == null)
                {
                    var closure = Closure(newItems);
                    resultState = new LR0State(closure);

                    calculatedStates.Add(new KeyValuePair<ClosureAction, LR0State>(new ClosureAction(newItems), resultState));
                }
            }
            
            return new KeyValuePair<LR0State, bool>(resultState, isNew);
        }

        public List<LR0State> CanonicalCollection()
        {
            var stateID = -1;
            var unprocessedStats = new Stack<LR0State>();
            var canonicalCollection = new List<LR0State>();

            var initalElements = augmentedGrammar.Productions[augmentedGrammar.StartingSymbol];
            var initalState = new LR0State(Closure(initalElements));
            unprocessedStats.Push(initalState);
            calculatedStates.Add(new KeyValuePair<ClosureAction, LR0State>(new ClosureAction(initalElements), initalState));

            while (unprocessedStats.Count != 0)
            {
                var currentState = unprocessedStats.Pop();
                stateID++;
                currentState.StateID = stateID;
                canonicalCollection.Add(currentState);

                Log("State:");
                Log(currentState);

                augmentedGrammar.AllSymbols.ForEach(symbol =>
                {
                    var gotoResult = Goto(currentState, symbol);
                    if (gotoResult.Key != null)
                    {
                        var state = gotoResult.Key;
                        var isNew = gotoResult.Value;
                        Log(symbol);
                        Log(state);

                        if (isNew == true)
                        {
                            unprocessedStats.Push(state);
                        }
                    }
                });
            }

            return canonicalCollection;
        }

        public bool IsAccepted(LR0State state)
        {
            if (state.Items.Count == 1)
            {
                var accItem = new LR0Item(augmentedGrammar.StartingSymbol, grammar.StartingSymbol + ".");
                if (accItem.Equals(state.Items[0]))
                    return true;
            }

            return false;
        }

        public bool IsShift(LR0State state)
        {
            foreach (var item in state.Items)
            {
                var index = item.rhs.IndexOf('.');
                if (index == item.rhs.Length - 1)
                    return false;
            }

            return true;
        }

        public bool IsReduce(LR0State state)
        {
            if (state.Items.Count == 1)
            {
                var item = state.Items[0];
                var index = item.rhs.IndexOf('.');
                if (index != item.rhs.Length - 1)
                    return false;
            }
            return true;
        }

        public int ReduceTo(LR0State state)
        {
            var item = state.Items[0];

            var lhsItem = item.lhs;
            var rhsItem = item.rhs.Substring(0, item.rhs.Length - 1);
            var newItem = new LR0Item(lhsItem, rhsItem);

            var index = 0;
            foreach(var originalItem in grammar.ProductionList)
            {
                if (originalItem.Equals(newItem))
                    return index;
                index++;
            }

            return -1;
        }

        public void CreateTable(List<LR0State> canonicalCollection)
        {
            Enumerable.Range(0, canonicalCollection.Count + 1).ToList().ForEach(index =>
            {
                table.Add(new List<string>());
                Enumerable.Range(0, grammar.AllSymbols.Count + 2).ToList().ForEach(j =>
                {
                    table[index].Add("");
                });
                table[index][0] = (index - 1).ToString();
            });

            table[0][0] = "nr";
            table[0][1] = "action";

            var index = 2;

            var symbolMap = new Dictionary<string, int>();

            grammar.AllSymbols.ForEach(symbol =>
            {
                table[0][index] = symbol;
                symbolMap[symbol] = index;
                index++;
            });

            canonicalCollection.ForEach(state =>
            {
                augmentedGrammar.AllSymbols.ForEach(symbol =>
                {
                    var gotoResult = Goto(state, symbol);
                    if (gotoResult.Key != null)
                    {
                        var gotoState = gotoResult.Key;
                        var i = state.StateID + 1;
                        var j = symbolMap[symbol];

                        table[i][j] = gotoState.StateID.ToString();
                    }
                });
            });

            canonicalCollection.ForEach(state =>
            {
                if (IsAccepted(state))
                    table[state.StateID + 1][1] = "acc";
                else
                if (IsShift(state))
                    table[state.StateID + 1][1] = "shift";
                else
                if (IsReduce(state))
                {
                    var productionIndex = ReduceTo(state);
                    table[state.StateID + 1][1] = productionIndex.ToString();
                }
                else
                {
                    Log("err");
                    Log(state);
                }    
            });

        }

        public string Parse(string sequence)
        {
            var canonicalCollection = CanonicalCollection();
            CreateTable(canonicalCollection);
            var index = 2;
            var symbolMap = new Dictionary<string, int>();
            var err = "";

            grammar.AllSymbols.ForEach(symbol =>
            {
                symbolMap[symbol] = index;
                index++;
            });

            var workingStack = new Stack<string>();
            var input = new Queue<string>();
            var output = new List<int>();

            workingStack.Push("$");
            workingStack.Push("0");

            foreach (var c in sequence)
            {
                input.Enqueue(c.ToString());
            }
            input.Enqueue("$");

            while (true)
            {
                var symbol = input.Peek();
                var nr = Int32.Parse(workingStack.Peek());

                if (table[nr + 1][1] == "acc")
                    break;
                else
                if(table[nr + 1][1] == "shift")
                {
                    if (!symbolMap.ContainsKey(symbol))
                    {
                        var state = canonicalCollection.Where(state => state.StateID == nr).FirstOrDefault();
                        err += "Err in parser\n";
                        if (state != null)
                        {
                            err += String.Format("{0}\n{1}\n{2}", "shift", symbol, state);
                        }
                        else
                        {
                            err += String.Format("{0}\n{1}\n{2}", "shift", symbol, "state is null");
                        }
                        return err;
                    }

                    var j = symbolMap[symbol];
                    workingStack.Push(symbol);
                    workingStack.Push(table[nr + 1][j]);

                    if (table[nr + 1][j] == "")
                    {
                        var state = canonicalCollection.Where(state => state.StateID == nr).FirstOrDefault();
                        err += "Err in parser\n";
                        if (state != null)
                        {
                            err += String.Format("{0}\n{1}\n{2}", "shift", symbol, state);
                        }
                        else
                        {
                            err += String.Format("{0}\n{1}\n{2}", "shift", symbol, "state is null");
                        }
                        return err;
                    }

                    input.Dequeue();
                }
                else
                {
                    var producutionNr = Int32.Parse(table[nr + 1][1]);
                    var production = grammar.ProductionList[producutionNr];

                    var nrOfPops = production.rhs.Length * 2;

                    while (nrOfPops > 0)
                    {
                        workingStack.Pop();
                        nrOfPops--;
                    }

                    var newNr = Int32.Parse(workingStack.Peek());
                    var j = symbolMap[production.lhs];

                    if (table[newNr + 1][j] == "")
                    {
                        var state = canonicalCollection.Where(state => state.StateID == nr).FirstOrDefault();
                        err += "Err in parser\n";
                        if (state != null)
                        {
                            err += String.Format("{0}\n{1}\n{2}", "shift", symbol, state);
                        }
                        else
                        {
                            err += String.Format("{0}\n{1}\n{2}", "shift", symbol, "state is null");
                        }
                        return err;
                    }

                    workingStack.Push(production.lhs);
                    workingStack.Push(table[newNr + 1][j]);

                    output.Add(producutionNr);
                }
            }

            var result = "";

            output.ForEach(prod => result = prod + ", " + result);
            result = result.Substring(0, result.Length - 2);

            return result;
        }
    }
}
