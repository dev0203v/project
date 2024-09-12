using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Kia.connect;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Kia
{
    /// <summary>
    /// Join_Page.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Join_Page : Page
    {
        static public NetworkStream stream;
        byte[] data = new byte[256];
        public Join_Page()
        {
            InitializeComponent();
            stream = Main.stream;
        }

        private void home_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/Main.xaml", UriKind.Relative)
            );
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            string jsonData = JsonConvert.SerializeObject(new
            {
                protocol = "회원가입요청",
                id = txt_join_ID.Text,
                pw = txt_join_PW.Text,
                name = txt_join_name.Text
            });

           /* MessageBox.Show(jsonData);*/

            Connect.send(stream, jsonData);


            byte[] recv_data = new byte[300];
            int bytes = stream.Read(recv_data, 0, recv_data.Length);
            string responses = Encoding.UTF8.GetString(recv_data, 0, bytes);


            JObject obj = JObject.Parse(responses);

            foreach (var item in obj)
            {
                responses = item.Value.ToString();
            }

            Console.WriteLine("Received: " + responses);

            if (responses == "회원가입 완료")
            {
                MessageBox.Show(responses);
                stream.Flush();
                NavigationService.Navigate(
                 new Uri("/Main.xaml", UriKind.Relative)
                 );
            }
            else if (responses == "중복된 아이디 입니다")
            {
                MessageBox.Show(responses);
            }

        }

        private void txt_join_ID_GotFocus(object sender, RoutedEventArgs e)
        {
            txt_join_ID.Clear();
        }

        private void txt_join_PW_GotFocus(object sender, RoutedEventArgs e)
        {
            txt_join_PW.Clear();
        }

        private void txt_join_name_GotFocus(object sender, RoutedEventArgs e)
        {
            txt_join_name.Clear();
        }
    }
}
