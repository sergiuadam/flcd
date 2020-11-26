using lab2.LR0.Models;
using System;
using System.Collections.Generic;
using System.Text;

namespace lab2.LR0.Actions
{
    public class ClosureAction
    {
        public List<LR0Item> InputItems;

        public ClosureAction(List<LR0Item> items)
        {
            InputItems = items;
        }

        public override bool Equals(object obj)
        {
            if (obj is ClosureAction action)
            {
                foreach (var item in InputItems)
                {
                    var hasPair = false;
                    foreach (var actionItem in action.InputItems)
                    {
                        if (item.Equals(actionItem))
                        {
                            hasPair = true;
                            break;
                        }
                    }

                    if (!hasPair)
                        return false;
                }
            }
            else
                return false;

            return true;
        }
    }
}
