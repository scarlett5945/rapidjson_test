#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <iostream>
#include <string>

using namespace std;

void Serialize_1()
{
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

    writer.StartObject();

    //1. 整数类型
    writer.Key("Int");
    writer.Int(1);

    //2. 浮点类型
    writer.Key("Double");
    writer.Double(12.0000001);

    //3. 字符串类型
    writer.Key("String");
    writer.String("This is a string");

    //4. 结构体类型
    writer.Key("Object");
    writer.StartObject();
    writer.Key("name");
    writer.String("qq849635649");
    writer.Key("age");
    writer.Int(25);
    writer.EndObject();

    //5. 数组类型
    //5.1 整型数组
    writer.Key("IntArray");
    writer.StartArray();
    //顺序写入即可
    writer.Int(10);
    writer.Int(20);
    writer.Int(30);
    writer.EndArray();

    //5.2 浮点型数组
    writer.Key("DoubleArray");
    writer.StartArray();
    for(int i = 1; i < 4; i++)
    {
        writer.Double(i * 1.0);
    }
    writer.EndArray();

    //5.3 字符串数组
    writer.Key("StringArray");
    writer.StartArray();
    writer.String("one");
    writer.String("two");
    writer.String("three");
    writer.EndArray();

    //5.4 混合型数组
    //这说明了，一个json数组内容是不限制类型的
    writer.Key("MixedArray");
    writer.StartArray();
    writer.String("one");
    writer.Int(50);
    writer.Bool(false);
    writer.Double(12.005);
    writer.EndArray();

    //5.5 结构体数组
    writer.Key("People");
    writer.StartArray();
    for(int i = 0; i < 3; i++)
    {
        writer.StartObject();
        writer.Key("name");
        writer.String("qq849635649");
        writer.Key("age");
        writer.Int(i * 10);
        writer.Key("sex");
        writer.Bool((i % 2) == 0);
        writer.EndObject();
    }
    writer.EndArray();

    writer.EndObject();

    string data = strBuf.GetString();
    cout << data << endl;
}

/**
 * {"Int":1,
 *  "Double":12.0000001,
 *  "String":"This is a string",
 *  "Object":{"name":"qq849635649","age":25},
 *  "IntArray":[10,20,30],
 *  "DoubleArray":[1.0,2.0,3.0],
 *  "StringArray":["one","two","three"],
 *  "MixedArray": ["one",50,false,12.005],
 *  "People":[{"name":"qq849635649","age":0,"sex":true},
 *            {"name":"qq849635649","age":10,"sex":false},
 *            {"name":"qq849635649","age":20,"sex":true}]}
 */

string data =
        "{\"Int\":1,"
        "\"Double\":12.0000001,"
        "\"String\":\"This is a string\","
        "\"Object\":{\"name\":\"qq849635649\",\"age\":25},"
        "\"IntArray\":[10,20,30],"
        "\"DoubleArray\":[1.0,2.0,3.0],"
        "\"StringArray\":[\"one\",\"two\",\"three\"],"
        "\"MixedArray\":[\"one\",50,false,12.005],"
        "\"People\":[{\"name\":\"qq849635649\",\"age\":0,\"sex\":true},"
        "{\"name\":\"qq849635649\",\"age\":10,\"sex\":false},"
        "{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}]}";

void parse() {
    //创建解析对象
    rapidjson::Document doc;
    //首先进行解析，没有解析错误才能进行具体字段的解析
    if(!doc.Parse(data.data()).HasParseError())
    {
        //1. 解析整数
        if(doc.HasMember("Int") && doc["Int"].IsInt())
        {
            cout << "Int = " << doc["Int"].GetInt() << endl;
        }
        //2. 解析浮点型
        if(doc.HasMember("Double") && doc["Double"].IsDouble())
        {
            cout << "Double = " << doc["Double"].GetDouble() << endl;
        }
        //3. 解析字符串
        if(doc.HasMember("String") && doc["String"].IsString())
        {
            cout << "String = " << doc["String"].GetString() << endl;
        }
        //4. 解析结构体
        if(doc.HasMember("Object") && doc["Object"].IsObject())
        {
            const rapidjson::Value& object = doc["Object"];
            if(object.HasMember("name") && object["name"].IsString())
            {
                cout << "Object.name = " << object["name"].GetString() << endl;
            }
            if(object.HasMember("age") && object["age"].IsInt())
            {
                cout << "Object.age = " << object["age"].GetInt() << endl;
            }
        }
        //5. 解析数组类型
        //5.1 整型数组类型
        if(doc.HasMember("IntArray") && doc["IntArray"].IsArray())
        {
            //5.1.1 将字段转换成为rapidjson::Value类型
            const rapidjson::Value& array = doc["IntArray"];
            //5.1.2 获取数组长度
            size_t len = array.Size();
            //5.1.3 根据下标遍历，注意将元素转换为相应类型，即需要调用GetInt()
            for(size_t i = 0; i < len; i++)
            {
                cout << "IntArray[" << i << "] = " << array[i].GetInt() << endl;
            }
        }
        //5.2 浮点型数组类型
        if(doc.HasMember("DoubleArray") && doc["DoubleArray"].IsArray())
        {
            const rapidjson::Value& array = doc["DoubleArray"];
            size_t len = array.Size();
            for(size_t i = 0; i < len; i++)
            {
                //为防止类型不匹配，一般会添加类型校验
                if(array[i].IsDouble())
                {
                    cout << "DoubleArray[" << i << "] = " << array[i].GetDouble() << endl;
                }
            }
        }
        //5.3 字符串数组类型
        if(doc.HasMember("StringArray") && doc["StringArray"].IsArray())
        {
            const rapidjson::Value& array = doc["StringArray"];
            size_t len = array.Size();
            for(size_t i = 0; i < len; i++)
            {
                //为防止类型不匹配，一般会添加类型校验
                if(array[i].IsString())
                {
                    cout << "StringArray[" << i << "] = " << array[i].GetString() << endl;
                }
            }
        }
        //5.4 混合型
        if(doc.HasMember("MixedArray") && doc["MixedArray"].IsArray())
        {
            const rapidjson::Value& array = doc["MixedArray"];
            size_t len = array.Size();
            for(size_t i = 0; i < len; i++)
            {
                //为防止类型不匹配，一般会添加类型校验
                if(array[i].IsString())
                {
                    cout << "MixedArray[" << i << "] = " << array[i].GetString() << endl;
                }
                else if(array[i].IsBool())
                {
                    cout << "MixedArray[" << i << "] = " << array[i].GetBool() << endl;
                }
                else if(array[i].IsInt())
                {
                    cout << "MixedArray[" << i << "] = " << array[i].GetInt() << endl;
                }
                else if(array[i].IsDouble())
                {
                    cout << "MixedArray[" << i << "] = " << array[i].GetDouble() << endl;
                }
            }
        }
        //5.5 结构体数组类型
        if(doc.HasMember("People") && doc["People"].IsArray())
        {
            const rapidjson::Value& array = doc["People"];
            size_t len = array.Size();
            for(size_t i = 0; i < len; i++)
            {
                const rapidjson::Value& object = array[i];
                //为防止类型不匹配，一般会添加类型校验
                if(object.IsObject())
                {
                    cout << "ObjectArray[" << i << "]: ";
                    if(object.HasMember("name") && object["name"].IsString())
                    {
                        cout << "name=" << object["name"].GetString();
                    }
                    if(object.HasMember("age") && object["age"].IsInt())
                    {
                        cout << ", age=" << object["age"].GetInt();
                    }
                    if(object.HasMember("sex") && object["sex"].IsBool())
                    {
                        cout << ", sex="  << (object["sex"].GetBool() ? "男" : "女") << endl;
                    }
                }
            }
        }
    }
    /**
     *    最后注意：因为rapidjson不会做安全校验，所以要自己做安全校验，以int整型为例
     * “if(object.HasMember("age") && object["age"].IsInt()) {}”
     * 这句校验很重要，既要校验有该子段，也要校验类型正确，否则会引发程序崩溃
     */
}

//遍历解析
void parse_1()
{
    // 这个是用于遍历json数组，用于不知道name的前提下
    string data = "{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}";
    rapidjson::Document dom;
    if(! dom.Parse(data.data()).HasParseError())
    {
        for (rapidjson::Value::ConstMemberIterator iter = dom.MemberBegin(); iter != dom.MemberEnd(); ++iter)
        {
            string name = (iter->name).GetString();
            const rapidjson::Value& value = iter->value;
            if(value.IsString())
            {
                cout << name << " : " << value.GetString() << endl;
            }
            else if(value.IsInt())
            {
                cout << name << " : " << value.GetInt() << endl;
            }
            else if(value.IsBool())
            {
                cout << name << " : " << value.GetBool() << endl;
            }
        }
    }
}

int main()
{
    //Serialize_1();
    parse_1();
    return 0;
}