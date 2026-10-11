# type1engine

跟随 TheCherno 的 *Sparky Engine*（"How To Make a Game Engine"）系列教程学习时写的 C++ / OpenGL 2D 游戏引擎。在教程框架的基础上，自己扩展了**音频系统**（Sound/SoundManager：多实例同播、暂停续播、循环开关、句柄自动回收）、**字体管理**（多字号中文渲染）和 **GBK→UTF-8 本地化文本转换**。

## 功能

- **窗口 / 输入**：GLFW 封装，键盘按下/单击、鼠标按下/单击/位置
- **2D 批渲染**：单 VBO + 索引缓冲，一个批次最多 60000 个精灵；demo 铺满 32×18 随机色块、每帧换色做压测
- **纹理**：FreeImage 加载（BMP / PNG 等），24/32 位入 GL
- **字体**：freetype-gl 纹理图集，微软雅黑 / Arial 多字号；`Label` 持有自己的文本，每帧提交
- **层级**：`Layer` / `TileLayer` / `Group`（变换栈 Push/Pop），Layer 析构自动释放全部 renderable
- **音频**：GorillaAudio 封装——按名字查找、同一条音效叠加多个实例（`Inst`）、暂停后记住播放位置、循环开关、播完句柄由回调标记、统一在 Update 里回收
- **工具**：ReadFile、GBK→UTF-8（`localeToUTF8`）、高精度计时器

## 目录结构

```
type1engine/
├─ main.cpp               # demo：随机色块压测 + 音效键盘演示
├─ type1engine.h          # 汇总头
├─ Ext/                   # freetype / freetype-gl 的 .lib
├─ System/
│  ├─ Audios/             # Sound / SoundManager（GorillaAudio 封装）
│  ├─ Fonts/              # Font / FontManager（freetype-gl 封装）
│  ├─ Graphics/           # Window / Shader / Texture / 缓冲 / 渲染器 / Layer
│  ├─ Shaders/            # shader.vert / shader.frag
│  └─ Utils/              # ReadFile / FreeImage 加载 / 计时器
└─ *.ttf *.bmp *.ogg ...  # demo 资源（含中文字体与中文文件名音效）
```

## 依赖

| 库 | 版本 |
| --- | --- |
| GLFW | 3.2.1（bin.WIN32） |
| GLEW | 2.0.0 |
| glm | — |
| FreeImage | — |
| FreeType | 2.7 |
| freetype-gl | master |
| GorillaAudio | 0.3.1 |

按原说明把这些库解压后与 `type1engine` 文件夹放在同一级。工程链接的是 `glfw3.lib; glew32s.lib; FreeImage.lib; freetype27MT.lib; freetype-gl.lib; gorilla.lib`，头文件/库路径当年配在 VS 全局的 VC++ Directories 里——换机器编译要么补上同样的全局配置，要么直接把 Include/Library 目录写进 vcxproj。

## 编译

- 工程：`type1engine.sln`，工具集 **v140（VS2015）**，Windows SDK **8.1**；新版 VS 打开时重定向到当前工具集即可
- 平台：Windows
- 源码为 **GBK 编码**（含中文资源路径与注释），用 UTF-8 打开会看到乱码，改代码时注意保持编码一致

## Demo 操作

运行后是 960×540 窗口：铺满随机色块压测批渲染，左上角 FPS / 精灵数（旋转组），左侧逐行列出每个声音实例的状态：

| 按键 | 作用 |
| --- | --- |
| ESC | 退出 |
| 按住左键拖动 | 把光源 uniform 移到鼠标位置 |
| 左键单击 | 播放爆炸音（exp） |
| 右键单击 | 叠加一个爆炸音实例 |
| 中键单击 | 切换 exp 循环开关 |
| N / M | test 音效 播放 / 停止 |
| B / 空格 | bgm 叠加实例 / 播放 |
| P / S | bgm 暂停 / 停止 |

## 更新（2026-10）

按 GorillaAudio 源码（[mewspring/gorilla-audio](https://github.com/mewspring/gorilla-audio)）与 OpenGL 的实际语义修了一批真 bug（构建环境不变）：

**音频**
- `GetSound` / `GetFont` 原来用 `==` 比较 `const char*`（比的是指针不是内容，全靠 MSVC `/GF` 字符串池合并侥幸能跑），改按内容比较
- 管理器的 map 删除后键留空洞，而按 `m_Sounds[i]` 索引遍历（`operator[]` 对不存在的键会插 nullptr 再崩溃），`Clean` 还会隔一个删一个；全部改迭代器遍历
- `Stop()` 原来只 destroy 不清条目：`ga_handle_destroy` 只置 DESTROYED 态、内存等 dispatch 释放，之后 `Play()` / `DeleteFinishedHandle` 继续解引用已 free 的句柄（UAF）；改为销毁同时清条目，释放交给 `gau_manager_update` 的 dispatch 兜底
- `Inst()` 原来把栈局部变量当回调上下文传出去，播完回调在 `Inst` 返回之后写它（写已失效的栈帧）；回调改为只调 `ga_handle_destroy`，不碰上下文

**图形**
- 建纹理误用 `glGenBuffers` 改 `glGenTextures`；位深不支持时补提示（原来静默空白）
- Shader 析构误用 `glDeleteShader` 改 `glDeleteProgram`；链接/校验状态误用 `glGetShaderiv`（对 program 查询无效、读到的是未初始化变量）改 `glGetProgramiv` / `glGetProgramInfoLog`
- 批渲染器析构补删 VAO；索引数组 `new[]` 配对 `delete[]`
- 键盘/鼠标回调对 `GLFW_KEY_UNKNOWN(-1)` 等越界索引加保护
- `DrawString` 图集缺字形（如中文配 Arial）原来直接 `exit(1)`，改跳过该字符
- `Label` 文本改 `std::string`：原来外部把栈缓冲赋给它（悬空）、声音状态标签每秒泄漏一份堆内存；`localeToUTF8` 改返回 `std::string`（原 static 缓冲非重入）
- 图片加载失败时 `m_dib` 未初始化、析构 Unload 野指针，补初始化

**Demo**
- `textures[4]` 补删；每秒一次的字符串堆分配泄漏清除
