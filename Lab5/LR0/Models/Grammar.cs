using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace lab2.LR0.Models
{
    public class Grammar
    {
        public List<string> Nonterminals { get; set; }
        public List<string> Terminals { get; set; }
        public Dictionary<string, List<string>> Productions { get; set; } = new Dictionary<string, List<string>>();
        public string StartingSymbol { get; set; }

        public List<string> AllSymbols = new List<string>();

        public static Grammar FromFile(string filePath)
        {
            var grammar = new Grammar();
            try
            {
                StreamReader fileReader = null;
                fileReader = new StreamReader(filePath);

                grammar.StartingSymbol = fileReader.ReadLine();
                grammar.Nonterminals = fileReader.ReadLine().Split(" ").ToList();
                grammar.Terminals = fileReader.ReadLine().Split(" ").ToList();
                grammar.AllSymbols.AddRange(grammar.Nonterminals);
                grammar.AllSymbols.AddRange(grammar.Terminals);

                var grammarProductionsRef = grammar.Productions;

                var line = "";
                while ((line = fileReader.ReadLine()) != null)
                {
                    var item = line.Split(new string[] { "->" }, StringSplitOptions.None);
                    var lhs = item[0];
                    var rhs = item[1];
                    if (!grammarProductionsRef.ContainsKey(lhs))
                        grammarProductionsRef[lhs] = new List<string>();
                    grammarProductionsRef[lhs].Add(rhs);
                }
            }
            catch (Exception ex)
            {
                //Log(ex)
                return null;
            }
            return grammar;
        }
    }
}
