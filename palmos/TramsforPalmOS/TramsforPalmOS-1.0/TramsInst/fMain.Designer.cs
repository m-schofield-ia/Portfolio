namespace TramsInst
{
    partial class fMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fMain));
            this.label1 = new System.Windows.Forms.Label();
            this.cCancel = new System.Windows.Forms.Button();
            this.cInstall = new System.Windows.Forms.Button();
            this.cProfile = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(272, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "To which profile should Trams for Palm OS be installed? ";
            // 
            // cCancel
            // 
            this.cCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cCancel.Location = new System.Drawing.Point(271, 81);
            this.cCancel.Name = "cCancel";
            this.cCancel.Size = new System.Drawing.Size(75, 23);
            this.cCancel.TabIndex = 9;
            this.cCancel.Text = "Cancel";
            this.cCancel.UseVisualStyleBackColor = true;
            this.cCancel.Click += new System.EventHandler(this.cCancel_Click);
            // 
            // cInstall
            // 
            this.cInstall.Location = new System.Drawing.Point(11, 81);
            this.cInstall.Name = "cInstall";
            this.cInstall.Size = new System.Drawing.Size(75, 23);
            this.cInstall.TabIndex = 8;
            this.cInstall.Text = "Install";
            this.cInstall.UseVisualStyleBackColor = true;
            this.cInstall.Click += new System.EventHandler(this.cInstall_Click);
            // 
            // cProfile
            // 
            this.cProfile.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cProfile.FormattingEnabled = true;
            this.cProfile.Location = new System.Drawing.Point(56, 36);
            this.cProfile.Name = "cProfile";
            this.cProfile.Size = new System.Drawing.Size(290, 21);
            this.cProfile.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 39);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Profile:";
            // 
            // fMain
            // 
            this.AcceptButton = this.cInstall;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cCancel;
            this.ClientSize = new System.Drawing.Size(361, 118);
            this.Controls.Add(this.cCancel);
            this.Controls.Add(this.cInstall);
            this.Controls.Add(this.cProfile);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(367, 140);
            this.MinimumSize = new System.Drawing.Size(367, 140);
            this.Name = "fMain";
            this.Text = "Install Trams for Palm OS";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button cCancel;
        private System.Windows.Forms.Button cInstall;
        private System.Windows.Forms.ComboBox cProfile;
        private System.Windows.Forms.Label label2;
    }
}

