using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
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
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Kia
{
    /// <summary>
    /// Login_Page.xaml에 대한 상호 작용 논리
    /// </summary>

    public partial class Login_Page : Page
    {

        static public NetworkStream stream;
        List<string> str_list_jobject = new List<string>();
        List<string> login_list = new List<string>();
        byte[] data = new byte[256];
        public Login_Page()
        {

            InitializeComponent();
            stream = Main.stream;
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/Join_Page.xaml", UriKind.Relative)
            );
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            string jsonData = JsonConvert.SerializeObject(new
            {
                protocol = "로그인요청",
                id = txt_ID.Text,
                pw = pw_PW.Password
            });

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

            if (responses == "로그인 완료")
            {
                stream.Flush();
                NavigationService.Navigate(
                 new Uri("/Menu_Page.xaml", UriKind.Relative)
                 );
            }
            else if (responses == "회원정보가 일치하지 않습니다")
            {
                MessageBox.Show(responses);
                txt_ID.Clear();
                pw_PW.Clear();
            }

        }

        private void txt_ID_GotFocus(object sender, RoutedEventArgs e)
        {
            txt_ID.Clear();
        }

        private void pw_PW_GotFocus(object sender, RoutedEventArgs e)
        {
            pw_PW.Clear();
        }
    }
}
