using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Kia.connect;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace Kia
{
    public partial class search : Page
    {
        static public NetworkStream stream;

        public search()
        {
            InitializeComponent();
            stream = Main.stream2;
        }

        private void main_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/Menu_Page.xaml", UriKind.Relative));
        }

        private void search__Click(object sender, RoutedEventArgs e)
        {
        
            string jsonData = JsonConvert.SerializeObject(new
            {
                protocol = "예측하기"
            });

            Connect.send2(stream, jsonData);

            byte[] recv_data = new byte[4000];
            int bytes = stream.Read(recv_data, 0, recv_data.Length);
            string recvmsg = Encoding.UTF8.GetString(recv_data, 0, bytes);

            JObject obj = JObject.Parse(recvmsg);

            string predictions = obj["predictions"].ToString();

            txt_result.Text = predictions;



            stat(obj);
        }

        public void stat(JObject obj)
        {
            // "data" 속성을 JArray로 파싱
            if (obj["data"] is JArray dataArray)
            {
                // JSON 데이터를 파싱하여 List<Statistic>으로 변환
                List<Stat_info> stat_data = new List<Stat_info>();

                foreach (var item in dataArray)
                {
                    if (item is JArray subArray && subArray.Count == 9)
                    {
                        stat_data.Add(new Stat_info
                        {
                            oWAR = subArray[0]?.ToString(),
                            dWAR = subArray[1]?.ToString(),
                            WAR = subArray[2]?.ToString(),
                            AVG = subArray[3]?.ToString(),
                            OBP = subArray[4]?.ToString(),
                            SLG = subArray[5]?.ToString(),
                            OPS = subArray[6]?.ToString(),
                            RePA = subArray[7]?.ToString(),
                            WRC = subArray[8]?.ToString()
                        });
                    }
                }

                // ListView에 데이터 바인딩
                stat_info.ItemsSource = stat_data;
            }
            else
            {
                // "data" 속성이 JArray가 아닌 경우 처리
                MessageBox.Show("Unexpected data format.");
            }

        }

    }

    public class Stat_info
    {
        public string oWAR { get; set; }
        public string dWAR { get; set; }
        public string WAR { get; set; }
        public string AVG { get; set; }
        public string OBP { get; set; }
        public string SLG { get; set; }
        public string OPS { get; set; }
        public string RePA { get; set; }
        public string WRC { get; set; }

    }
}
