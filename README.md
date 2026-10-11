# type1engine
*Game Engine Development with learning "Sparky Engine (How To Make a Game Engine)"*

To compile this code you need the following libraries.Put them with type1engine folder together.
 
* GorillaAudio-0.3.1-bin 
* freetype-gl-master
* freetype-2.7
* FreeImage
* glm
* glew-2.0.0
* glfw-3.2.1.bin.WIN32

# 更新（2026-10）

按 GorillaAudio（mewspring/gorilla-audio）与 OpenGL 的实际语义修了一批真 bug（构建环境不变，仍为 VS 工程 + 上述库）：

* 音频：`GetSound`/`GetFont` 原来用 `==` 比较 `const char*`（比的是指针）改按内容比较；管理器 map 删除键后留空洞而 `operator[]` 会插 nullptr，改迭代器遍历；`Stop()` 后句柄悬空仍被 `Play()` 解引用（UAF），改为销毁同时清条目；播放完成回调原来写已失效的栈变量，去掉；`DeleteFinishedHandle` 判空顺序修正。
* 图形：纹理创建误用 `glGenBuffers` 改 `glGenTextures`；着色器程序析构误用 `glDeleteShader` 改 `glDeleteProgram`，链接/校验状态误用 `glGetShaderiv` 改 `glGetProgramiv`；批渲染器析构补删 VAO；`delete` 改 `delete[]`；按键/鼠标回调对 `GLFW_KEY_UNKNOWN(-1)` 等越界索引加保护；`DrawString` 缺字形时跳过该字符而不是 `exit(1)`；`Label` 文本改 `std::string`（原来外部赋栈缓冲悬空、每秒泄漏一份）；图片位深不支持时给提示。
* Demo：`textures[4]` 泄漏补删；每秒一次的字符串堆分配泄漏清除。
