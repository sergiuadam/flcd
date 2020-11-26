using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using lab2.LR0.Actions;
using lab2.LR0.Models;

namespace lab2.LR0
{
    public class LR0Parser
    {
        private const bool IS_LOGGER_ACTOVE = true;

        private Grammar grammar;
        private AugmentedGrammar augmentedGrammar;
        private List<KeyValuePair<ClosureAction, LR0State>> calculatedStates = new List<KeyValuePair<ClosureAction, LR0State>>();

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
            var unprocessedStats = new Stack<LR0State>();
            var canonicalCollection = new List<LR0State>();

            var initalElements = augmentedGrammar.Productions[augmentedGrammar.StartingSymbol];
            var initalState = new LR0State(Closure(initalElements));
            unprocessedStats.Push(initalState);
            calculatedStates.Add(new KeyValuePair<ClosureAction, LR0State>(new ClosureAction(initalElements), initalState));

            while (unprocessedStats.Count != 0)
            {
                var currentState = unprocessedStats.Pop();
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
    }
}
