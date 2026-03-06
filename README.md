# Sudoku-Game

一个基于 **SAT（布尔可满足性）** 的控制台小项目，包含两部分功能：

- **SAT 求解器**：读取 DIMACS CNF 文件并使用 DPLL 算法求解，输出/保存结果（`.res`）。
- **Hanidoku（蜂窝数独）**：从内置样例 CNF 随机抽取题面，生成对应规则 CNF，调用 SAT 求解后解析并展示蜂窝数独解答，同时支持对单格答案进行校验查询。

> 语言：C / C++（Windows 控制台程序，代码中使用了 `windows.h`、`system("cls")` 等）

---

## 项目结构

- `main.cpp`：主菜单与交互逻辑（SAT 与 Hanidoku 两大模块的入口）
- `def.h`：基础定义与数据结构（子句链表、宏、常量等）
- `SAT.h`：CNF 读取、子句集链表操作、DPLL 求解、结果保存
- `HaniDoku.h`：Hanidoku 规则生成（写 CNF）、题面读取、结果解析与打印、单格查询

---

## 功能说明

程序启动后会进入菜单（`SAT and Hanidoku Slover`），可选择 0~8：

### SAT 模块

1. **read cnf**  
   输入 CNF 文件名（DIMACS 格式），读取并构建子句链表。

2. **print cnf**  
   打印当前已加载的 CNF 子句集（逐子句输出文字）。

3. **DPLL**  
   对当前 CNF 执行 DPLL 求解，并按 SAT 竞赛常见格式打印：
   - `s <result>`：是否可满足（TRUE/ FALSE）
   - `v ...`：当可满足时输出每个变元的取值（正数表示真，负数表示假）
   同时将结果保存到 `.res` 文件（由输入文件名改后缀得到）。

4. **DPLL_pre**  
   另一版本的 DPLL（代码里是 `DPLL_prev2`），选择变元策略与主版本不同，用于对比/实验。

### Hanidoku 模块

5. **createHan**  
   - 随机生成一个题面文件名：`h0X.cnf`（X 由 `RandN` 控制，当前为 1~5）
   - 从对应的 `h0X.cnf` 读取部分已给定格子作为题面
   - 调用 `transrules()` 在该文件中写入规则（CNF 约束）
   - 打印当前题面（使用 ASCII 蜂窝样式展示，空格以 `.` 表示）

6. **solveHan**  
   - 读取（/生成）CNF 子句集
   - 调用 DPLL 求解并保存 `.res`
   - 将 `.res` 中 `v` 行的赋值解析回 `HaniDoku[10][10]`，得到最终解

7. **showHan**  
   将当前 `HaniDoku` 数组以蜂窝 ASCII 形式打印出来。

8. **query**  
   输入 `(row, col, value)`，用于验证某一格填写是否正确；如果错误会给出该格的正确值。

---

## CNF / 求解结果文件

### 输入 CNF
SAT 部分支持 DIMACS CNF（示例格式）：

- 注释行以 `c` 开头
- `p cnf <boolnum> <clsnum>`
- 后续每行一个子句，以 `0` 结束

### 输出 `.res`
求解结束后会把输入文件扩展名改为 `.res` 并写入：

- `s <ans>`：是否可满足
- `v ...`：赋值序列（可满足时）
- `t <ms>`：用时（毫秒）

---

## 构建与运行（Windows）

由于代码中使用 `windows.h` / `Sleep()` / `system("cls")`，建议在 Windows 环境编译运行。

示例（MinGW g++）：

```bash
g++ -std=c++11 -O2 main.cpp -o SudokuGame
SudokuGame.exe
```

> 如果你使用 Visual Studio，新建控制台项目后把这几个源文件加入工程即可。

---

## 说明与限制

- Hanidoku 的题面来源依赖仓库外部/同目录下的 `h01.cnf ~ h0N.cnf`（由 `RandN` 控制，当前 `RandN=5`）。若缺少这些文件，`createHan` 会打不开文件。
- SAT 子句集使用链表结构存储，DPLL 在递归分支中会复制/销毁子句集，适合教学/实验用途，但规模很大时性能有限。
- 当前菜单/界面输出为中英文混合（主要为中文注释）。

---

## License

未指定（如需可补充 MIT / Apache-2.0 等）。