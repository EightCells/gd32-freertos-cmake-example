def generate_repeat_macros(max_n):
    code = []
    
    # 头文件保护宏和注释
    code.append("/* gernerated by scripts */\n")
    code.append("#ifndef __REPEATE_DEF_H__")
    code.append("#define __REPEATE_DEF_H__\n")
    
    # CONCAT 和 X_ITEM 宏
    code.append("#define CONCAT(a, b)       a##_##b")
    code.append("#define X_ITEM(x, i)       CONCAT(x, i)")
    code.append("#define X_ITEM_S(x, i, s)  x##_i##_##s\n")
    
    # 生成 REPEAT_1 到 REPEAT_30
    for i in range(1, max_n + 1):
        if i == 1:
            code.append(f"#define REPEAT_{i}(m, x) m(x, {i})")
            code.append(f"#define REPEAT_S_{i}(m, x, s) m(x, {i}, s)")
        else:
            code.append(f"#define REPEAT_{i}(m, x) REPEAT_{i-1}(m, x), m(x, {i})")
            code.append(f"#define REPEAT_S_{i}(m, x, s) REPEAT_S_{i-1}(m, x, s), m(x, {i}, s)")
    
    # REPEAT 分发宏
    code.append("\n#define REPEAT(n, m, x) CONCAT(REPEAT, n)(m, x)")
    code.append("#define REPEAT_S(n, m, x, s) CONCAT(REPEAT_S, n)(m, x, s)\n")
    
    # 最终 GENERATE 宏
    code.append("#define GENERATE_ARRAY(x, n)   REPEAT(n, X_ITEM, x)")
    code.append("#define GENERATE_ARRAY_S(x, n, s) REPEAT_S(n, X_ITEM_S, x, s)\n")


    
    code.append("#endif // __REPEATE_DEF_H__")
    return "\n".join(code)

# 生成头文件内容
header_content = generate_repeat_macros(max_n=30)

# 保存到文件
with open("./repeat_def.h", "w") as f:
    f.write(header_content)

print("头文件已生成：repeat_def.h")