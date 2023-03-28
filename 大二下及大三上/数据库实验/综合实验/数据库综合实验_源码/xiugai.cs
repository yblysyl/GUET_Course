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
    public partial class xiugai : Form
    {
        string ConnectString;
        public xiugai(string str) { 
            InitializeComponent( );
            ConnectString = str;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = "update ";
            SqlConnection Conn = new SqlConnection(ConnectString);
            if (textBox1.Text == ""||textBox2.Text=="") return;
            else
            {

                if (textBox2.Text != "") str = str + textBox1.Text + " set " + textBox3.Text + " where " + textBox2.Text;
                else str = str + textBox1.Text + " set " + textBox3.Text;

            }

            SqlCommand cmd = new SqlCommand(str, Conn);
            Conn.Open();
            try
            {
                cmd.ExecuteNonQuery();
                Conn.Close();
                textBox3.Text = "修改成功";
            }
            catch
            {
                textBox1.Text = "输入有误，请重新你输入";
                return;
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
