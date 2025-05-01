
## vscode


```
gcc -v
clang -v
brew install gcc

gcc-13 -v


macOS 的 debugger 是 lldb,，得自己安装gdb
brew install gdb
whereis gdb
WARNING: Debugger executable '/usr/local/bin/gdb' is not signed. As a result, debugging may not work properly.
ERROR: Unable to start debugging. Unexpected GDB output from command "-exec-run". Unable to find Mach task port for process-id 91593: (os/kern) failure (0x5).
 (please check gdb is codesigned - see taskgated(8))

1. 打开 Keychain Access
2. 菜单项Keychain Access --> Certificate Assistant --> Create a Certificate... ，点击Create a Certificate... 
3. 给证书选个名字，此处是 gdb_codesign，可以用其他名字; 设置 Identity Type 为 Self Signed Root ; 设置 Certificate Type 为 Code Signing ; 勾选 Let me override defaults，然后Continue
4. 接下来默认即可（中间截图省略），点击几次Continue，直到为证书指定位置（Specify a Location For The Certificate），设置 Keychain 为 System ，然后 Create，输入密码

确保 keychain 是 System keychain
security find-certificate -c gdb_codesign |grep System.keychain
确保证书没有过期
security find-certificate -p -c gdb_codesign | openssl x509 -checkend 0


```

## 代码格式化

```bash
# 格式名可选：LLVM, Google, Chromium, Mozilla, WebKit。
clang-format -style=Google -dump-config > .clang-format
```
