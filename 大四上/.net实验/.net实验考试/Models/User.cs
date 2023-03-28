using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Kaoshi.Models
{
    public class User
    {


        [Key]
        public int UserId { get; set; }

        [Display(Name = "身份证号")]
        [StringLength(20, MinimumLength = 6, ErrorMessage = "×")]
        public string Shenfenzhenghao { get; set; }

        [Display(Name = "用户名", Description = "4-20个字符。")]
        [Required(ErrorMessage = "×")]
        [StringLength(20, MinimumLength = 4, ErrorMessage = "×")]
        public string UserName { get; set; }
      
        [Display(Name = "密码")]
        [Required(ErrorMessage = "×")]
        [StringLength(512)]
        public string Password { get; set; }
      
 
        [Display(Name = "电话号码", Description = "常用的联系电话（手机或固话），固话格式为：区号 - 号码。")]
        public string Dianhua { get; set; }
      
    }
    public class userDBContext2 : DbContext
    {
        public DbSet<User> Usersks { get; set; }
        public DbSet<Xuanze> Xuanzes { get; set; }
    }
    public class Xuanze
    {
        [Key]
        public int UserId { get; set; }

        [Display(Name = "身份证号")]
        [StringLength(20, MinimumLength = 6, ErrorMessage = "×")]
        public string Shenfenzhenghao { get; set; }

        public string Leibie { get; set; }

    }

}
