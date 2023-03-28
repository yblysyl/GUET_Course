using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Kaoshi.Models
{
    public class Denglu
    {
        //用户名
        [Display(Name = "身份证号", Description = "4-20 个字符。")]
        [Required(ErrorMessage = "x")]
        [StringLength(20, MinimumLength = 4, ErrorMessage = "x")]
        public string Shenfenzhenghao { get; set; }
        //密码
        [Display(Name = "密码", Description = "6-20 个字符。")]
        [Required(ErrorMessage = "x")]
        [StringLength(20, MinimumLength = 6, ErrorMessage = "x")]
        [DataType(DataType.Password)]
        public string Password { get; set; }
    }
}