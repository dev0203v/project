using LiveCharts.Wpf;
using LiveCharts;
using LiveCharts.Defaults;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
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
using System.Net.Sockets;
using System.Diagnostics;
using Newtonsoft.Json.Linq;
using TesseractSharp.Hocr;
using Newtonsoft.Json;

namespace Kia
{
    /// <summary>
    /// graph.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class graph : Page
    {
        static public NetworkStream stream;
        int count_ = 0;
        double[] count = new double[5];
        public graph()
        {
            InitializeComponent();

            stream = Main.stream2;

            oWARValues = new ChartValues<double>();
            dWARValues = new ChartValues<double>();
            WARValues = new ChartValues<double>();
            AVGValues = new ChartValues<double>();
            OBPValues = new ChartValues<double>();
            SLGValues = new ChartValues<double>();
            OPSValues = new ChartValues<double>();
            RePAValues = new ChartValues<double>();
            WRCValues = new ChartValues<double>();

            DataContext = this;
        }

        public ChartValues<double> oWARValues { get; set; }
        public ChartValues<double> dWARValues { get; set; }
        public ChartValues<double> WARValues { get; set; }
        public ChartValues<double> AVGValues { get; set; }
        public ChartValues<double> OBPValues { get; set; }
        public ChartValues<double> SLGValues { get; set; }
        public ChartValues<double> OPSValues { get; set; }
        public ChartValues<double> RePAValues { get; set; }
        public ChartValues<double> WRCValues { get; set; }

        private void main_Click(object sender, RoutedEventArgs e)
        {
            stream.Close();
            NavigationService.Navigate(
                new Uri("/Menu_Page.xaml", UriKind.Relative)
                );
        }

        private async void send_Click(object sender, RoutedEventArgs e)
        {

            string jsonData = JsonConvert.SerializeObject(new
            {
                protocol = "그래프보기"
            });

            Connect.send2(stream, jsonData);

            byte[] recv_data = new byte[4000];
            int bytes = stream.Read(recv_data, 0, recv_data.Length);
            string recvmsg = Encoding.UTF8.GetString(recv_data, 0, bytes);

            JObject obj = JObject.Parse(recvmsg);

            // 차트 데이터 초기화
            oWARValues.Clear();
            dWARValues.Clear();
            WARValues.Clear();
            AVGValues.Clear();
            OBPValues.Clear();
            SLGValues.Clear();
            OPSValues.Clear();
            RePAValues.Clear();
            WRCValues.Clear();

            // "data" 속성을 JArray로 파싱
            if (obj["data"] is JArray dataArray)
            {
                foreach (var item in dataArray)
                {
                    if (item is JArray subArray && subArray.Count == 9)
                    {
                        // 차트 데이터 추가
                        oWARValues.Add(Convert.ToDouble(subArray[0]));
                        dWARValues.Add(Convert.ToDouble(subArray[1]));
                        WARValues.Add(Convert.ToDouble(subArray[2]));
                        AVGValues.Add(Convert.ToDouble(subArray[3]));
                        OBPValues.Add(Convert.ToDouble(subArray[4]));
                        SLGValues.Add(Convert.ToDouble(subArray[5]));
                        OPSValues.Add(Convert.ToDouble(subArray[6]));
                        RePAValues.Add(Convert.ToDouble(subArray[7]));
                        WRCValues.Add(Convert.ToDouble(subArray[8]));
                    }
                }
            }
            else
            {
                // "data" 속성이 JArray가 아닌 경우 처리
                MessageBox.Show("Unexpected data format.");
            }
        }
    }
}







