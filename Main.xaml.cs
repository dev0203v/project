using System;
using System.Collections.Generic;
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
using Kia.connect;
namespace Kia
{
    /// <summary>
    /// Main.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Main : Page
    {
        static public string ip = "10.10.21.111";
        static public int port = 8790;
        static public int port2 = 5791;
        static public NetworkStream stream;
        static public NetworkStream stream2;
        public Main()
        {
            InitializeComponent();
            stream = Connect.connect(ip, port);
            stream2 = Connect.connect2(ip, port2);
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Login_Page.xaml", UriKind.Relative)
                );
        }
        private void join_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Join_Page.xaml", UriKind.Relative)
                );
        }
    }
}
