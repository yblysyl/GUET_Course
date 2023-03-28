using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 数据库综合实验
{
    public partial class Form2 : Form
    {
        string ConnectString;
        public Form2(string str)
        {
            InitializeComponent();
            ConnectString = str;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            chaxun form2exe = new chaxun(ConnectString);
            form2exe.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            xiugai form2exe = new xiugai(ConnectString);
            form2exe.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
           shanchu form2exe = new shanchu(ConnectString);
            form2exe.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            charu form2exe = new charu(ConnectString);
            form2exe.Show();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            统计 form2exe = new 统计(ConnectString);
            form2exe.Show();
        }
    }
}
