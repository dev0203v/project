using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
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

namespace Kia
{
    /// <summary>
    /// Menu_Page.xaml에 대한 상호 작용 논리
    /// </summary>
    
    public partial class Menu_Page : Page
    {
        static public NetworkStream stream;
        public Menu_Page()
        {
            InitializeComponent();
            stream = Main.stream;
        }

        private void graph_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/graph.xaml", UriKind.Relative)
            );
        }

        private void rank_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/search.xaml", UriKind.Relative)
            );
        }

        private void home_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
          new Uri("/Main.xaml", UriKind.Relative)
          );
        }
    }
}
