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
    public partial class chaxun : Form
    {
        string ConnectString;
        public chaxun(string str)
        {
            InitializeComponent();
            ConnectString = str;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            string str= "select ";
            SqlConnection Conn = new SqlConnection(ConnectString);
            if (textBox1.Text == "") return;
            else
            {
                if (textBox4.Text != "") str = str + "top " + textBox4.Text;
                if (textBox2.Text != "") str = str + " "+textBox2.Text;
                else str = str + " * ";
                str = str + " from " + textBox1.Text;
                if (textBox3.Text != "") str = str + " where " + textBox3.Text;
            }
                
                Conn.Open();
          try
             {
                DataSet ds = new DataSet();
               
                SqlDataAdapter da = new SqlDataAdapter(str, Conn);
                da.Fill(ds, "perform");
                dataGridView1.DataSource = ds.Tables["perform"];
                Conn.Close();
                for (int i = 0; i < dataGridView1.Columns.Count; i++)
                    dataGridView1.Columns[i].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;

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
