using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Threading;

namespace NeuralNetworkInterface
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private bool mouse_down = false;
        private Bitmap number = new Bitmap(80, 80);
        private Bitmap clear = new Bitmap(80, 80);
        private void button1_Click(object sender, EventArgs e)
        {
            string path = System.IO.Path.GetDirectoryName(Application.ExecutablePath);
            int[] a = new int[50000];
            /*  int width = Convert.ToInt32(panel1.Width);
              int height = Convert.ToInt32(panel1.Height);
              Bitmap bmp = new Bitmap(width, height);
              panel1.DrawToBitmap(bmp, new Rectangle(0, 0, width, height));

              bmp.Save(path+@"\CurrentNumber.png", ImageFormat.Jpeg);


          Image newImage = Image.FromFile(path + @"\CurrentNumber.png");
          Bitmap b1 = new Bitmap(newImage);*/

            for (int j = 0; j < 20; j ++)
            {
                for (int k = 0; k < 20; k++)
                {
                    Color col = number.GetPixel(j*4, k*4);
                    if (col.Name != "0")
                        a[k * 20 + j] = 1;
                    else
                        a[k * 20 + j] = 0;
                }
            }
            label2.Text = path;
           
            string FileName = path + @"\input1.txt";
            System.IO.StreamWriter file = new System.IO.StreamWriter(FileName, false, System.Text.Encoding.Default);
            file.Write("");
            file.Close();
            System.IO.StreamWriter file1 = new System.IO.StreamWriter(FileName, true, System.Text.Encoding.Default);
           
            for (int j = 0; j < 400; j++)
            {
                if (j % 20 == 0 && j != 0)
                    file1.WriteLine();
                if (a[j] == 1)
                    file1.Write("1 ");
                else
                    file1.Write("0 ");
            }

          Process.Start(path + @"\NeuralNetwork.exe");
            Thread.Sleep(1000);
            file.Close();
            file1.Close();
            string text = System.IO.File.ReadAllText(path + @"\output.txt");
            label2.Text = text;
            clear = new Bitmap(clear, panel1.Size);
            panel1.BackgroundImage = clear;
            number = new Bitmap(80, 80);
            
        
    }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            mouse_down = true;
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            mouse_down = false;
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (mouse_down)
            {
                number = new Bitmap(number, panel1.Size);
                panel1.BackgroundImage = number;
                if (e.X - 2 >= 0 && e.X + 2 < number.Width && e.Y - 2 >= 0 && e.Y + 2 < number.Height)
                {
                    for (int i = -2; i <= 2; i++)
                        for (int j = -2; j <= 2; j++)
                            number.SetPixel(e.X + i, e.Y + j, Color.Black);

                }
            }

        }
    }
}
