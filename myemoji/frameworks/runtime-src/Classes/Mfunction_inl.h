//
//  Mfunction_inl.h
//  
//
//  
//
//

#ifndef __matinal__Mfunction_inl__
#define __matinal__Mfunction_inl__

#include “cocos2d.h”

USING_NS_CC;


struct emojiString
{
    bool _isEmoji;
    std::string _string;
    
    emojiString():_isEmoji(false),_string(""){}
    emojiString(std::string str, bool b):_isEmoji(b),_string(str){}
    
    //分割字符串得到表情字符代码
    static std::vector<emojiString> split_emoji(const std::string& str);
};

struct M
{
    // 其他基本类型转换为字符串
    template<typename T>
    inline static std::string to_s(T arg)
    {
        std::stringstream ss;
        ss << arg;
        return ss.str();
    }
    
    // 字符串转换为布尔型
    static bool s_b(const std::string& str);
    static bool s_b(const char* str);
    
    // 字符串转换为整型
    static int s_i(const std::string& str);
    static int s_i(const char* str);
    
    // 字符串转换为长整型
    static long long s_ll(const std::string& str);
    static long long s_ll(const char* str);
    
    // 字符串转换为浮点数
    static float s_f(const std::string& str);
    static float s_f(const char* str);
    
    static double s_d(const std::string& str);
    static double s_d(const char* str);
    
    // 浮点数近似相等
    static bool equals(float a,float b);
    
    // 去除一个小数的多余有效位数
    static float interceptionDecimal(float num, int significand);

    // 去除一个小数的多余有效位数 并且 四舍五入
    static float interceptionDecimalRound(float num, int significand);
    
    // 四舍五入 返回浮点
    static float round(float num, int significand);
    
    // 四舍五入 返回整数
    static int roundInt(float num);
    
    // 百分比概率触发 10000为100%
    static bool probability(int percentage);
    
    //字符串分割函数
    static std::vector<std::string> split(const std::string& str,
                                          const std::string& token);
    
    //字符串分割函数
    static std::vector<std::string> split(unsigned char* bytes, ssize_t size,
                                          const std::string& token);
    
    //字符串0,0,0,0转化为Color4B
    static Color4B s4B(const std::string& str);
    
    //字符串0,0,0转化为Color3B
    static Color3B s3B(const std::string& str);
    
    //字符串0,0转化为Size
    static Size sSize(const std::string& str);
    
    // 创建遮罩
    static Node* createTouchMask(Node* node);
    
    // 获取时间(秒)
    static time_t t_s();
    
    // 获取时间(毫秒)
    static timeval t_val();
    
    // 获取时间(年、月、日、时、分、秒)
    static tm* t_tm();
    
    // 字符串转换到长整型
    static long long to_ll(const std::string& ll_str);
    
    // 长整型转换到字符串
    static std::string ll_to(long long ll);
    
    // 节点缩放
    static void node_scale(Node* modelNode, Node* scaleNode);
	
	// 解密
	static bool decrypt(unsigned char* data,unsigned long fileSize);
};


#endif /* defined(__matinal__Mfunction_inl__) */
