﻿using System;
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
    public partial class charu : Form
    {
        string ConnectString;
        public charu(string str)
        {
            InitializeComponent();
            ConnectString = str;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = "insert into ";
            SqlConnection Conn = new SqlConnection(ConnectString);
            if (textBox1.Text == "" || textBox3.Text == "") return;
            else
            {   if(textBox2.Text!="")
                str = str + textBox1.Text + "("+ textBox2.Text+ ") values"+"(" + textBox3.Text+")";
                else str = str + textBox1.Text + " values" + "(" + textBox3.Text + ")";

            }

            SqlCommand cmd = new SqlCommand(str, Conn);
            Conn.Open();
            try
            {
                cmd.ExecuteNonQuery();
                Conn.Close();
                textBox2.Text = "插入成功";
            }
            catch
            {
                textBox2.Text = "输入有误，请重新你输入";
                return;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
