using System.Net;
using System.Net.Sockets;
using System.Text;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            timer1.Start();
            timer1.Interval = 1000;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            TcpListener server = new TcpListener(IPAddress.Any, 9999);
            server.Start();

            TcpClient client = server.AcceptTcpClient();
            NetworkStream ns = client.GetStream();

            byte[] hello = new byte[100];
            hello = System.Text.Encoding.Default.GetBytes("hello from windows server");

            ns.Write(hello, 0, hello.Length);
            byte[] msg = new byte[1024];

            ns.Read(msg, 0, msg.Length);
            string msg123 = Encoding.ASCII.GetString(msg);

            textBox1.Text = msg123;

            server.Stop();
        }
    }
}