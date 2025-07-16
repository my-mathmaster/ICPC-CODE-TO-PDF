## 项目概述

本项目旨在通过自动化工作流将算法模板快速打包成PDF文件，便于代码的整理与分享。

## 工作流程

1. **YAML配置文件生成**
   通过`format.py`脚本遍历`src/`目录，自动生成`scl.yaml`配置文件，定义代码的目录结构和文件信息。
2. **LaTeX文档生成**
   通过`gen2.py`脚本读取`scl.yaml`文件，生成包含代码块、行号和描述的LaTeX文档（`code.tex`）。
3. **PDF编译与输出**
   通过Makefile自动化编译LaTeX文档，生成最终的PDF文件。

## 技术栈

- **Python脚本开发**
  使用Python3实现文件遍历、YAML配置生成、LaTeX代码生成等功能。
- **LaTeX排版技术**
  利用`lstlisting`环境实现代码块的高亮显示，结合`mdframed`环境实现描述信息的排版。
- **自动化构建工具**
  通过Makefile实现从代码到PDF的全流程自动化构建。

## 使用方式

### 环境要求

- 操作系统：Linux/Mac OS X（Windows未测试）
- 编译环境：texlive xelatex
- 所需字体：宋体(SimSun)、黑体(SimHei)和Courier New
  （若系统中不包含这些字体，可在`format.tex`中修改配置）

### 编译步骤

1. 确保Linux/Mac OS X系统已安装texlive xelatex环境。

2. 在项目根目录下使用`make`工具编译：

   ```bash
   make
   ```

   由于每一行代码的fingerprint使用了label，在添加新代码后需要编译两次（Makefile中已经默认编译两次）。
