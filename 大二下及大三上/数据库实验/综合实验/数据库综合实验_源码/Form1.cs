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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = "Server="+textBox1.Text+";DataBase="+textBox2.Text+";uid="+textBox3.Text+";pwd="+textBox4.Text;

            SqlConnection Conn = new SqlConnection(str);
            try{ Conn.Open();
                Conn.Close();
            }
            catch {
                textBox3.Text = "连接错误 ";
                    return; }
           
            Form2 form2exe = new Form2(str);
            form2exe.Show();
        }

    }
}
