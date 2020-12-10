using System;
using System.Collections.Generic;
using System.Text;

namespace lab2.LR0.Models
{
    public class AugmentedGrammar : Grammar
    {
        public new Dictionary<string, List<LR0Item>> Productions { get; set; }

        public static AugmentedGrammar Augement(Grammar grammar)
        {
            var augmentedStartingSymbol = grammar.StartingSymbol + "`";

            var augmentedNonterminals = new List<string>();
            augmentedNonterminals.Add(augmentedStartingSymbol);
            augmentedNonterminals.AddRange(grammar.Nonterminals);

            var augmentedTerminals = new List<string>();
            augmentedTerminals.AddRange(grammar.Terminals);

            var augmentedSymbols = new List<string>();
            augmentedSymbols.AddRange(augmentedNonterminals);
            augmentedSymbols.AddRange(augmentedTerminals);

            var augmentedProductions = new Dictionary<string, List<LR0Item>>();

            augmentedProductions[augmentedStartingSymbol] = new List<LR0Item>() { new LR0Item(augmentedStartingSymbol, "." + grammar.StartingSymbol) };

            foreach(var productionPair in grammar.Productions)
            {
                var lhs = productionPair.Key;
                var lr0Items = new List<LR0Item>();

                productionPair.Value.ForEach(rhs =>
                {
                    var item = new LR0Item(lhs, "." + rhs);
                    lr0Items.Add(item);
                });

                augmentedProductions[lhs] = lr0Items;
            }

            return new AugmentedGrammar()
            {
                Nonterminals = augmentedNonterminals,
                Terminals = augmentedTerminals,
                Productions = augmentedProductions,
                StartingSymbol = augmentedStartingSymbol,
                AllSymbols = augmentedSymbols
            };
        }
    }
}
