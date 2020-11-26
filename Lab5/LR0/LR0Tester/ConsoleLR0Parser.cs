﻿using System;
using System.Collections.Generic;
using System.Text;

namespace lab2.LR0.LR0Tester
{
    class ConsoleLR0Parser
    {
        private LR0Parser parser = LR0Parser.FromFile("lr01.txt");

        public void Run()
        {
            while (true)
            {
                parser.CanonicalCollection();

                Console.WriteLine("1 - nonterminals");
                Console.WriteLine("2 - terminals");
                Console.WriteLine("3 - set of productions");
                Console.WriteLine("4 - production for a given nonterminal");

                var command = Console.ReadLine();

                if (command.Equals("1"))
                {
                    var str = "";
                    parser.GetNonterminals().ForEach(nonterminal => str += nonterminal + " ");
                    Console.WriteLine(str);
                }
                if (command.Equals("2"))
                {
                    var str = "";
                    parser.GetTerminals().ForEach(terminal => str += terminal + " ");
                    Console.WriteLine(str);
                }
                if (command.Equals("3"))
                {
                    var str = "";
                    var productions = parser.GetProductions();

                    foreach (var pair in productions)
                    {
                        pair.Value.ForEach(rhs =>
                        {
                            str += pair.Key + "->" + rhs + "\n";
                        });
                    }

                    Console.WriteLine(str);
                }
                if (command.Equals("4"))
                {
                    var nonterminal = Console.ReadLine();
                    var str = "";
                    parser.GetProductionsFor(nonterminal).ForEach(rhs => str += nonterminal + "->" + rhs + "\n");
                    Console.WriteLine(str);
                }
            }
        }
    }
}
