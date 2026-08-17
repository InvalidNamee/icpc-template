# 协作约定

## 基本流程

1. 从 `main` 创建功能分支。
2. 一个 Pull Request 尽量只新增或修改一个算法模块。
3. 提交前运行 `make pdf`，确认中文、公式和代码均正常显示。
4. 等待 GitHub Actions 的 PDF 构建通过，再进行合并。

## 新增模块

假设要新增 `graph/max-flow`：

```text
content/graph/max-flow/
  module.tex
  note.tex
  code.hpp       # 没有代码时可以省略
```

在 `content/graph/chapter.tex` 中加入：

```latex
\ICPCIncludeModule{content/graph/max-flow}
```

`module.tex` 建议保持很短，只负责声明模块并组装文件：

```latex
\ICPCModule{最大流}
\ICPCMeta{复杂度}{根据具体算法填写}
\ICPCNote
\ICPCCode[Dinic]{code.hpp}
```

## LaTeX 内容规则

- 一句话一行，减少多人协作时的 Git 冲突。
- 内容文件只使用 `theme/icpcbook.sty` 提供的语义命令，不在模块中自行设置颜色和字体。
- 常用结论使用 `icpcresult`，易错点使用 `icpcwarning`，补充说明使用 `icpcnote`。
- 数学符号优先使用 `mathtools`、`amssymb` 提供的标准写法。
- 不在 `note.tex` 中嵌入大段 C++；代码放进独立源码文件并通过 `\ICPCCode` 导入。
- 第三方代码必须在模块说明中写明来源和许可证，不能直接复制来源不明的模板。

## C++ 内容规则

- 代码片段默认主文件已经包含所需标准库并声明 `using namespace std;`，不重复书写 `#include` 和 `std::`。
- 需要维护内部状态的算法和数据结构统一封装为 `struct`，避免使用散落的全局数组。
- 文件应保持可复制，避免依赖仓库内部的隐式宏。
- 当前 CI 只验证 PDF；源码编译、单元测试和压力测试将在后续阶段加入。
- 即使暂未自动测试，也应在 `module.tex` 中如实标记验证状态。
