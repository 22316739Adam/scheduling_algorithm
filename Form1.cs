using System;
using System.Windows.Forms;
using System.IO; 
using System.Drawing;
using System.Runtime.InteropServices;

public class AlgoMethods
{
    [StructLayout(LayoutKind.Sequential)]
    public struct process {
        public int id, arrival_time, burst_time, init_bust, priority; 
        public IntPtr next; 
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct Pair {
        public IntPtr p; 
        public int n; 
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct exporting_process {
        public int id, arrival_time, burst_time, priority; 
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct exporting_Pair {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public exporting_process[] tot_pro;
        public int n;
    }

    [DllImport("imp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern void build_input(string path, out exporting_Pair inp); 

    [DllImport("imp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern void fcfs(ref exporting_Pair inp, string path);

    [DllImport("imp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern void sjf_preemptive(ref exporting_Pair inp, string path); 

    [DllImport("imp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern void priority_preemptive(ref exporting_Pair inp, string path); 
};

public class Form1 : Form
{
    String path="";
    public Form1()
    {
        this.Text = "Process Scheduling Stimulation";
        this.Size = new Size(1000, 500);

        Label title = new Label() {
            Text = "Process Scheduling Stimulation", 
            Font = new Font("Times New Roman", 30, FontStyle.Bold), 
            Left = 250, 
            TextAlign = ContentAlignment.MiddleCenter, 
            AutoSize = true,
        }; 

        RichTextBox inp_format = new RichTextBox()
        {
            Text = "For the format of the input that would be passed to the algorithm; Write at each line first the ID of the process (should be odered) followed by the arrival time, burst time then the priority value.",
            Top = 100,
            Left = 500,
            Width = 400,
            Height = 100,
            Font = new Font("Times New Roman", 15),
            ReadOnly = true,
            AutoSize = true
        };

        RichTextBox output_exp = new RichTextBox() 
        {
            Text = "To check the output, view \"output.txt\" in the directory where ahead of each algorithm, the order of processes in which they would be processed then the average waiting time specific to that algoritm", 
            Top = 230,
            Left = 500,
            Width = 400, 
            Height = 100,
            Font = new Font("Times New Roman", 15),
            ReadOnly = true,
            AutoSize = true
        };

        Label desc = new Label()
        {
            Text = "Please pass the input file here:",
            Left = 0,
            Top = 100,
            Font = new Font("Times New Roman", 15),
            AutoSize = true
        };

        Button upload_btn = new Button() {
            Text = "Upload", 
            Font = new Font("Times New Roman", 15),
            Top = 100, 
            Left = 370,
            AutoSize = true
        };

        upload_btn.Click += (sender, e) => {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Text files | *.txt"; // Filtering files so that .txt only could be uploaded
            dialog.Multiselect = false; // Allowing only one file to be uploaded 
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                path = dialog.FileName; // Storing path to the input file
            }
        };

        Button so_btn = new Button() {
            Text = "Compute",
            Font = new Font("Times New Roman", 15),
            Top = 230, 
            Left = 370, 
            AutoSize = true
        };

        so_btn.Click += (sender, e) => {
            AlgoMethods.exporting_Pair inp = new AlgoMethods.exporting_Pair(); 
            inp.tot_pro = new AlgoMethods.exporting_process[10]; 
            AlgoMethods.build_input(path, out inp); 

            AlgoMethods.exporting_Pair inp_c = inp;
            inp_c.tot_pro = (AlgoMethods.exporting_process[])inp.tot_pro.Clone();

            AlgoMethods.exporting_Pair inp_cc = inp;
            inp_cc.tot_pro = (AlgoMethods.exporting_process[])inp.tot_pro.Clone();        
            
            
            AlgoMethods.fcfs(ref inp, @"C:\wkin\output.txt"); 
            AlgoMethods.sjf_preemptive(ref inp_c, @"C:\wkin\output.txt"); 
            AlgoMethods.priority_preemptive(ref inp_cc, @"C:\wkin\output.txt"); 
        };

        Controls.AddRange(new Control[] {
            desc, title, upload_btn, so_btn, inp_format, output_exp
        });
    }
}