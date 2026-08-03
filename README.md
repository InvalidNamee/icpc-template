# ICPC 算法模板库

这是一个面向多人协作的中文 ICPC 模板库框架。
最终文档使用纵向 A4、双栏排版，算法说明、数学结论和 C++ 源码按模块隔离。

## 当前设计

- 中文优先：XeLaTeX + `ctex`，默认使用 TeX Live 自带的 Fandol 中文字体。
- 低墨打印：纵向 A4 双栏、白底蓝灰细线，无大面积色块。
- 清晰代码：8pt 代码字体、无行号、保留完整外边框和跨栏续标题。
- 模块隔离：每个算法目录拥有独立的 `module.tex`、`note.tex` 和可选源码文件。
- GitHub 协作：Pull Request 合并，GitHub Actions 自动编译并上传 PDF。
- 完整知识库：不限制文档页数，不做比赛版裁剪。

## 本地构建

需要 TeX Live 2026 或功能相当的发行版，其中应包含 XeLaTeX、`latexmk`、`ctex`、`minted` 和 `tcolorbox`。
`minted` 需要 `latexminted` 或 Pygments，因此构建命令会启用受控的 `shell-escape`。

```bash
make pdf
```

生成文件位于 `output/pdf/icpc-template.pdf`。
持续预览可以使用：

```bash
make watch
```

## 内容结构

```text
content/
  contents.tex                 # 章节顺序
  graph/
    chapter.tex                # 本章模块顺序
    dijkstra/
      module.tex               # 模块入口与元信息
      note.tex                 # 中文说明、公式和结论
      code.hpp                 # 可选 C++ 模板
config/
  team.tex                     # 学校、队名、队员等占位信息
theme/
  icpcbook.sty                 # 全局主题；普通内容 PR 不应修改
```

添加内容前请阅读 [CONTRIBUTING.md](CONTRIBUTING.md)。

## 设计来源

排版方向参考了 [teamnote.sty](https://github.com/ho94949/teamnote.sty) 的纵向双栏示例；模块组织思想参考了 [KACTL](https://github.com/kth-competitive-programming/kactl)。
本仓库当前没有引入上述项目的算法代码。
