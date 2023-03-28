import state
import os

@state.stateful
class User(object):
    class SignIn(state.State):
        default = True
        @state.behavior
        def signIn(self, usrName, usrPwd):
            if usrName == 'admin' and usrPwd == 'admin':
                print('Successfully logged in.')
                #如果成功登录就切换至工作状态
                state.switch(self, User.SignedIn)

    class SignedIn(state.State):
        @state.behavior
        def createFile(self):
            with open('test.txt', 'w') as fp:
                fp.write('created')
                
        @state.behavior
        def modifyFile(self):
            if not os.path.exists('test.txt'):
                return
            with open('test.txt', 'a+') as fp:
                fp.write('ok')
                
        @state.behavior
        def deleteFile(self):
            if os.path.exists('test.txt'):
                os.remove('test.txt')
                
        @state.behavior
        def listFile(self):
            for f in os.listdir('.'):
                print(f)

zhang = User()
zhang.signIn('admin', 'admin')
zhang.listFile()
zhang.createFile()
zhang.modifyFile()
zhang.listFile()
zhang.deleteFile()
