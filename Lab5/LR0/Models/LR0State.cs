using System;
using System.Collections.Generic;
using System.Text;

namespace lab2.LR0.Models
{
    public class LR0State
    {
        public LR0State(List<LR0Item> items)
        {
            Items = items;
        }

        public List<LR0Item> Items { get; set; }

        public override string ToString()
        {
            var str = "";

            Items.ForEach(item =>
            {
                str += item.ToString() + "\n";
            });

            return str;
        }
    }
}
