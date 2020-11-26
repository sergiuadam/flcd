using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace lab2.LR0.Models
{
    public enum SymbolType
    {
        Terminal,
        Nonterminal,
        Dot,
        Unknown
    }

    public class LR0Item
    {
        public string lhs { get; set; }
        public string rhs { get; set; }

        private SymbolType GetSymbolType(char symbol)
        {
            if (symbol == '.')
                return SymbolType.Dot;
            if (Char.IsUpper(symbol))
                return SymbolType.Nonterminal;
            if (Char.IsLower(symbol))
                return SymbolType.Terminal;

            return SymbolType.Unknown;
        }

        private int GetDotIndex()
        {
            var index = 0;
            foreach (var symbol in rhs)
            {
                if (GetSymbolType(symbol) == SymbolType.Dot)
                    return index;
                index++;
            }

            return -1;
        }

        public LR0Item(string lhs, string rhs)
        {
            this.lhs = lhs;
            this.rhs = rhs;
        }

        public string GetNonterminalAfterDot()
        {
            var dotIndex = GetDotIndex();
            if (dotIndex == rhs.Length - 1)
                return null;

            var symbol = rhs[dotIndex + 1];

            if (GetSymbolType(symbol) != SymbolType.Nonterminal)
                return null;

            return symbol.ToString();
        }

        public string GetSymbolAfterDot()
        {
            var dotIndex = GetDotIndex();
            if (dotIndex == rhs.Length - 1)
                return null;

            var symbol = rhs[dotIndex + 1];

            return symbol.ToString();
        }

        public LR0Item MoveDot()
        {
            var dotIndex = GetDotIndex();

            if (dotIndex == rhs.Length - 1)
                return this;

            var rhsBuilder = new StringBuilder(rhs);
            rhsBuilder[dotIndex] = rhsBuilder[dotIndex + 1];
            rhsBuilder[dotIndex + 1] = '.';

            var newLR0Item = new LR0Item(lhs, rhsBuilder.ToString());
            return newLR0Item;
        }

        public override bool Equals(object obj)
        {
            if (obj is LR0Item lr0Item)
            {
                if (!lr0Item.lhs.Equals(lhs))
                    return false;
                if (!lr0Item.rhs.Equals(rhs))
                    return false;
            }
            else
                return false;

            return true;
        }

        public override string ToString()
        {
            return lhs + "->" + rhs;
        }
    }
}
