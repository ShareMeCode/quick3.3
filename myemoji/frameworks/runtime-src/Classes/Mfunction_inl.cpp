#include "Mfunction_inl.h"

// -------------------------------------------接口方法------------------------------------------

const std::string emoji_start_str = "(";
const std::string emoji_end_str = ")";
//分割字符串得到表情字符代码
std::vector<emojiString> emojiString::split_emoji(const std::string& str)
{
    std::vector<emojiString> e_s;
    if (str == "")
	return e_s;
    size_t startPos = 0;
    size_t endPos = 0;
    // 第一个起始字符
    size_t start_pos1 = str.find(emoji_start_str, endPos);
    // 与第一个起始字符配对的结束字符
    size_t end_pos1 = str.find(emoji_end_str, start_pos1);
    size_t start_pos2 = str.find(emoji_start_str, start_pos1+1);
    while (start_pos2 != std::string::npos && start_pos2 < end_pos1) {
        // 查找到最近与之匹配的 ")"
        start_pos1 = start_pos2;
        start_pos2 = str.find(emoji_start_str, start_pos1+1);
    }
    // 确保 ")" 的位置在 "(" 在之后, 并且保证 "(" ")" 之间有字符存在，以保证不会出现 "[]" 的情况，但"[]]"算是有效表情字符串
    while (endPos != std::string::npos && end_pos1 <= start_pos1 + 1) {
        end_pos1 = str.find(emoji_end_str, end_pos1+1);
    }
    while (start_pos1 != std::string::npos && end_pos1 != std::string::npos) {
        
        // 截取上一个 emoji 与下一个 emoji 之间的普通字符串
        if (start_pos1 > endPos + 1 || endPos == 0) {
            // 从上一个 emoji 的字符位置的下一个开始截取, 到下一个 emoji 开始字符的前一个位置
            int startIndex = endPos + 1;
            int number = start_pos1 - endPos - 1;
            // 如果第一个 emoji 之前有普通字符串
            // 对位置进行修正，从 0 开始， 对长度经行修正，因为字符位置0也占一个长度，所以要加 1 的长度
            if (endPos == 0) {
                startIndex = 0;
                number += 1;
            }
            e_s.push_back(emojiString(str.substr(startIndex, number), false));
        }
        // 截取 emoji 字符串
        e_s.push_back(emojiString(str.substr(start_pos1, end_pos1 - start_pos1 + 1) , true));
        
        // 重置数据
        startPos = start_pos1;
        endPos = end_pos1;
        start_pos1 = str.find(emoji_start_str, endPos);
        end_pos1 = str.find(emoji_end_str, start_pos1);
        // 确保 ")" 的位置在 "(" 在之后
        while (endPos != std::string::npos && end_pos1 <= start_pos1 + 1) {
            end_pos1 = str.find(emoji_end_str, end_pos1+1);
        }
    }
    // str中 没有 符合要求的字符串
    if (startPos == std::string::npos || endPos == std::string::npos) {
        e_s.push_back(emojiString(str, false));
    }
    // str中 有 符合要求的字符串，若末尾还有多余字符串，将其加入非符合要求的字符中
    if (startPos != std::string::npos && endPos != std::string::npos) {
	if ( endPos < str.size()-1 && endPos != 0)
        	e_s.push_back(emojiString(str.substr(endPos+1), false));
	else if (endPos == 0)
        	e_s.push_back(emojiString(str.substr(endPos), false));
    }
    
    return e_s;
}

// 字符串转换为布尔型
bool M::s_b(const std::string& str)
{
    int value = atoi(str.c_str());
    M_ASSERT(value == 1 || value == 0, "s_b 参数str不是0或者1:[%s]", str.c_str());
    return value;
}
bool M::s_b(const char* str)
{
    int value = atoi(str);
    M_ASSERT(value == 1 || value == 0, "s_b 参数str不是0或者1:[%s]", str);
    return value;
}

// 字符串转换为整型
int M::s_i(const std::string& str)
{
    return atoi(str.c_str());
}
int M::s_i(const char* str)
{
    return atoi(str);
}

// 字符串转换为长整型
long long M::s_ll(const std::string& str)
{
    return atoll(str.c_str());
}
long long M::s_ll(const char* str)
{
    return atoi(str);
}

// 字符串转换为浮点数
float M::s_f(const std::string& str)
{
    return atof(str.c_str());
}
float M::s_f(const char* str)
{
    return atof(str);
}
double M::s_d(const std::string& str)
{
    return atof(str.c_str());
}
double M::s_d(const char* str)
{
    return atof(str);
}

// 浮点数近似相等
bool M::equals(float a,float b)
{
    return fabs(a - b) < FLT_EPSILON;
}

// 去除一个小数的多余有效位数
float M::interceptionDecimal(float num, int significand)
{
    return ((float)((int)(num * pow(10,significand)))) / pow(10,significand);
}
// 去除一个小数的多余有效位数 并且 四舍五入
float M::interceptionDecimalRound(float num, int significand)
{
    return ((float)((int)(round(num,significand) * pow(10,significand)))) / pow(10,significand);
}

// 四舍五入 返回浮点
float M::round(float num, int significand)
{
    int round_float = 0;
    if (num > 0)
    {
        return num + 0.5*pow(0.1,significand);
    }
    else
    {
        return num - 0.5*pow(0.1,significand);
    }
    return round_float;
}
// 四舍五入 返回整数
int M::roundInt(float num)
{
    int round_int = 0;
    if (num > 0)
    {
        round_int = num + 0.5;
    }
    else
    {
        round_int = num - 0.5;
    }
    return round_int;
}

// 百分比概率触发 10000为100%
bool M::probability(int percentage)
{
    return rand()%10000 < percentage;
}

//字符串分割函数
std::vector<std::string> M::split(const std::string& str, const std::string& token)
{
    std::vector<std::string> vect;
    ssize_t indexBegin = 0;
    ssize_t indexEnd = 0;
    while ((indexEnd = str.find_first_of(token, indexBegin)) != std::string::npos)
    {
        auto temp = str.substr(indexBegin,indexEnd-indexBegin);
        vect.push_back(temp);
        indexBegin = indexEnd + 1;
    }
    vect.push_back(str.substr(indexBegin,str.size()-indexBegin));
    return vect;
}

//字符串分割函数
std::vector<std::string> M::split(unsigned char* bytes, ssize_t size, const std::string& token)
{
    char* temp = new char[size + 1];
    memcpy(temp,bytes,size);
    temp[size] = '\0';
    std::vector<std::string> vect = split(temp,token);
    delete[] temp;
    return vect;
}

//字符串0,0,0,0转化为Color4B
Color4B M::s4B(const std::string& str)
{
    auto color4b = M::split(str,",");
    M_ASSERT(color4b.size() == 4, "M::s4B: str size != 4:[%s]", str.c_str());
    
    if (color4b.size() == 4)
    {
        return Color4B(M::s_i(color4b[0]),
                       M::s_i(color4b[1]),
                       M::s_i(color4b[2]),
                       M::s_i(color4b[3]));
    }
    return Color4B::WHITE;
}

//字符串0,0,0转化为Color3B
Color3B M::s3B(const std::string& str)
{
    auto color3b = M::split(str,",");
    M_ASSERT(color3b.size() == 3, "M::s3B: str size != 3:[%s]", str.c_str());
    
    if (color3b.size() == 4)
    {
        return Color3B(M::s_i(color3b[0]),
                       M::s_i(color3b[1]),
                       M::s_i(color3b[2]));
    }
    return Color3B::WHITE;
}

//字符串0,0转化为Size
Size M::sSize(const std::string& str)
{
    auto size = M::split(str,",");
    M_ASSERT(size.size() == 2, "M::sSize: str size != 2:[%s]", str.c_str());
    
    if (size.size() == 2)
    {
        return Size(M::s_f(size[0]),
                    M::s_f(size[1]));
    }
    return Size::ZERO;
}

// 创建遮罩
Node* M::createTouchMask(Node* node)
{
    auto listenerNode = Node::create();
    node->addChild(listenerNode);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    listener->onTouchBegan = [=](Touch*, Event*){
        eventDispatcher->dispatchCustomEvent("Mui_touchMask");
        M_INFO("touchMask effect");
        return true;
    };
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, listenerNode);
    return listenerNode;
}

// 获取时间(秒)
time_t M::t_s()
{
    return time(nullptr);
}

// 获取时间(毫秒)
timeval M::t_val()
{
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, nullptr);
    return nowTimeval;
}

// 获取时间(年月日)
tm* M::t_tm()
{
    time_t t = time(nullptr);
    return localtime(&t);
}

// 字符串转换到长整型
long long M::to_ll(const std::string& ll_str)
{
    std::string str;
    if (std::string(ll_str.begin(), ll_str.begin() + 3) != "ll_")
    {
        str.assign(ll_str.begin() + 3, ll_str.end());
    }
    else
    {
        M_ASSERT(0, "Mnet::to_ll:重复转换");
    }
    
    long long ll = M::s_ll(str);
    
    return ll;
}

// 长整型转换到字符串
std::string M::ll_to(long long ll)
{
    std::string str = M::to_s(ll);
    std::string ll_str = "ll_" + str;
    return ll_str;
}

// 节点缩放
void M::node_scale(Node* model, Node* node)
{
    auto modelSize = model->getContentSize();
    auto nodeSize = node->getContentSize();
    
    float scale = 1;
    // 选择缩放比例小的缩放
    if (nodeSize.width > nodeSize.height)
    {
        // 缩放比例
        scale = modelSize.width / nodeSize.width;
        
        // 位置居中
        auto posY = (modelSize.height/nodeSize.height - scale)*nodeSize.height/2;
        node->setPositionY(node->getPositionY() + posY);
    }
    else
    {
        // 缩放比例
        scale = modelSize.height / nodeSize.height;
        
        // 位置居中偏移
        auto posX = (modelSize.width/nodeSize.width - scale)*nodeSize.width/2;
        node->setPositionX(node->getPositionX() + posX);
    }
    node->setScale(scale);
}

// 解密
bool M::decrypt(unsigned char* data,unsigned long fileSize)
{
	const char* targets="Copyright@Boilgame.com";
	int targetLength=strlen(targets);
	
	if(fileSize <= targetLength){// 不够标示长度直接返回
		return false;
	}
	
	// 检查标示
	char* bytes = new char[targetLength+1];
	memcpy(bytes,data,targetLength);
	bytes[targetLength] = '\0';
	std::string target(bytes);
	if (target.compare(targets)!=0) {//没有标示表示是明文
		return false;
	}
	
	//unencrype file
	int tmp;
	for (int i = 22; i < fileSize; i++) {
		tmp=data[i];
		
		if (tmp >= 0 && tmp < 64) {
			tmp = tmp + 192;
		} else if (tmp >= 64 && tmp < 128) {
			tmp = tmp + 64;
		} else if (tmp >= 128 && tmp < 192) {
			tmp = tmp - 64;
		} else if (tmp >= 192 && tmp <= 256) {
			tmp = tmp - 192;
		}
		
		data[i]=tmp;
	}
	return true;
}

// --------------------------------------------内部方法-----------------------------------------
