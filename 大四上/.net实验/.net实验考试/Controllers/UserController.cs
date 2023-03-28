using Kaoshi.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Security;

namespace Kaoshi.Controllers
{
    public class UserController : Controller
    {
     
        userDBContext2 db = new userDBContext2();
        public ActionResult Index()
        {
            return View(db.Usersks);
        }
        public ActionResult Index2()
        {
            return View(db.Xuanzes);
        }
        public ActionResult Zhuce()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Zhuce(User userReg)
        {
            string shenfenzhenghao = userReg.Shenfenzhenghao;
             //db.Usersks.Where(rrrr => rrrr.Shenfenzhenghao == shenfenzhenghao).FirstOrDefault();
            
                User _user = userReg;
                _user.Password = userReg.Password;
                _user.UserName = userReg.UserName;
                db.Usersks.Add(_user);
                db.SaveChanges();
         
            return View("Index", db.Usersks);
        }



        public ActionResult Login()
        {
            FormsAuthentication.SignOut();
            return View();
        }
        [HttpPost]
        public ActionResult Login(Denglu login)
        {
            string shenfenzhenghao = login.Shenfenzhenghao;
            string password = login.Password;
            var result = "23";//db.Usersks.Where(u => u.Shenfenzhenghao == shenfenzhenghao && u.Password ==password).FirstOrDefault();
            if (result == null)
            {
                ModelState.AddModelError("Message", "登录失败！");
                return View("Login");
            }
            else
            {
                FormsAuthentication.SetAuthCookie(login.Shenfenzhenghao, false);
                return RedirectToAction("Index");
            }
        }


        public ActionResult Xuanze()
        {
            return View();
        }
        [HttpPost]
        public ActionResult Xuanzeq()
        {

            string username = HttpContext.User.Identity.Name;
            // var result = db.Usersks.Where(u => u.Shenfenzhenghao == username).FirstOrDefault();

            Xuanze x1 = new Xuanze();
            x1.Shenfenzhenghao = username;
            x1.Leibie = Request.Form["级"];
            db.Xuanzes.Add(x1);
            db.SaveChanges();
            return View("Index2");

        }







    }
}