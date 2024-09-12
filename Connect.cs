using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading.Tasks;

namespace Kia.connect
{
    public class Connect
    {
        private TcpClient Client;

        private NetworkStream Stream;

        private string IP = Main.ip;

        private int Port = Main.port;

        private int Port2 = Main.port2;


        public Connect() { connect_(); }

        static public NetworkStream connect(string ip, int port)
        {
            TcpClient client = new TcpClient(ip, port);
            NetworkStream stream = client.GetStream();
            return stream;
        }
        static public NetworkStream connect2(string ip, int port2)
        {
            TcpClient client = new TcpClient(ip, port2);
            NetworkStream stream = client.GetStream();
            return stream;
        }
        async static public void send(NetworkStream stream, string message)
        {
            byte[] data = Encoding.UTF8.GetBytes(message);
            await stream.WriteAsync(data, 0, data.Length);
        }
        async static public void send2(NetworkStream stream, string message)
        {
            byte[] data = Encoding.UTF8.GetBytes(message);
            await stream.WriteAsync(data, 0, data.Length);
        }

        public int connect_()
        {
            Debug.WriteLine("서버연결");
            try
            {
                //서버와 연결
                Client = new TcpClient(IP, Port);
                //데이터 송수신
                Stream = Client.GetStream();
            }
            catch (Exception ex)
            {
                //서버 연결 실패
                Debug.WriteLine($"{ex.Message}");
                return -1;
            }

            return 1;
        }

        public void disconnectServer()
        {
            Stream.Close();
            Client.Close();
            Debug.WriteLine("stream 해제");
        }

        async public void send_i(byte[] image)
        {
            int image_size = image.Length;
            await Stream.WriteAsync(image, 0, image_size);
        }
        async Task ReceiveMessages()
        {
            byte[] data = new byte[4096];
            while (true)
            {
                int bytes = await Stream.ReadAsync(data, 0, data.Length);
                string receivedMessage = Encoding.UTF8.GetString(data, 0, bytes);
                if (receivedMessage == "q")
                {
                    break;
                }
                //Console.WriteLine("Received: {0}", receivedMessage);
            }
        }
    }
}
