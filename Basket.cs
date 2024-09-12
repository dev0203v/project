using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Salmon.Models
{
    public class Basket
    {
        private string menu_name;
        public string Menu_name
        {
            get { return menu_name; }
            set { menu_name = value; }
        }

        private int menu_price;

        public int Menu_price
        {
            get { return menu_price; }
            set { menu_price = value; }
        }


        private int menu_cnt;

        public int Menu_cnt
        {
            get { return menu_cnt; }
            set { menu_cnt = value; }
        }

        private int total_price;

        public int Total_price
        {
            get { return total_price; }
            set { total_price = value; }
        }
    }
}
