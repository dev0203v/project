using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Salmon
{
    /// <summary>
    /// Order.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Order : Page
    {
        public Order()
        {

            InitializeComponent();
            txt_total_price.Text = Main_menu.total_price.ToString() + "원";
            Main_menu.total_price = 0;

        }

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/home.xaml", UriKind.Relative)
            );
        }
    }
}
