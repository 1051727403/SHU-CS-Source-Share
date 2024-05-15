# cov验收

## 网址

-----------------------------------------------------------

疫情可视化

http://47.100.249.168:9999/#/mappage 全国现有确诊

http://47.100.249.168:9999/#/trendpage 全国新增趋势

http://47.100.249.168:9999/#/shanghai 上海新增趋势

http://47.100.249.168:9999/#/helppage 上海求助信息统计

-----------------------------------------------------------

大家好，我是胡才郁。我做的主题是基于Flask与Vue的疫情数据可视化。这个作业它涉及到的知识比较多，涉及Python爬虫、Python网络编程、数据库操作、Flask搭建Web后端、Vue.js搭建Web前端、服务器部署、Echart做数据可视化等等。



#### 前端

| 技术  | 说明         |
| ----- | ------------ |
| Vue   | 前端框架     |
| Axios | 前端HTTP框架 |

#### 数据可视化

| 技术        | 说明             |
| ----------- | ---------------- |
| Echart  | JavaScript数据可视化 |
| matplotlib     | Python数据可视化 |
| seaborn | Python数据可视化 |

#### 后端

| 技术    | 说明         |
| ------- | ------------ |
| Flask   | 后端服务器   |
| MySQL   | 数据库       |
| PyMySQL | 数据库连接池 |

#### 爬虫

| 技术      | 说明         |
| --------- | ------------ |
| requesets | 请求数据接口 |

#### 部署

| 技术       | 说明             |
| ---------- | ---------------- |
| nginx      | 反向代理         |





那我的介绍就顺着数据流通的方向进行介绍。



首先第一步将网站的数据爬取到本地。

此处使用了Python网络爬虫分别爬取了三个网站。腾讯疫情数据来获取疫情的实时数据、丁香园来获取疫情的谣言与最新新闻、我们来帮你是一个上海抗疫互助网站。 我爬取了从2月份到至今的疫情数据、1000多条谣言数据、10000多条上海求助信息。

由于像腾讯这些网站他们的数据API接口还是比较复杂的，并且没有详细的API文档介绍，所以我只选取了部分自己能力范围内可以处理的数据。比如我简单展示一下爬虫处理时的数据嵌套由多么的复杂。拿腾讯疫情数据接口为例，我访问的接口，展示每个省的数据时，包含的字段由很多。



第二步是将爬取到的数据做持久化操作。

此处采用的是pymysql连接本地mysql数据库，并且把我需要的数据存成4张表，分别存全国疫情信息、上海疫情信息、中高风险地区、上海求助信息。



第三步是使用Flask，编写后端接口。

使用Flask作为后端服务器，连接mysql数据库提供后端接口。比如此处我访问我的api接口。这个接口是用来返回随时间变化全国疫情数据的变化，这个数据就是由Flask后端编写返回成json格式。

第四步是使用Vue.js+echart作为前端的可视化。

就比如大家这四个网址之中看到的，他们的内部数据并不是写死的，而是动态地调用后端的数据。比如这个疫情地图，他访问的数据就是调用的后端接口。并且这个可视化可以根据地区内确诊人数动态的显示地区。

此外就是两个趋势图，分别展示了中国与上海目前的疫情情况，并且支持折线图与条形图的切换。



最后一步为了能让大家能够在家就能访问到这个作业，把它部署到了阿里云的服务器上，并且使用了nginx对于端口进行了反向代理。使用nuhup命令部署后端服务，我可以直接查看后端服务器被访问的信息。



之后关于数据分析部分进行讲解，谣言关键词、新闻发布数量随时间变化等指标进行了分析。也对与上海求助信息进行语义文本分析，绘制词云图。



那这些就是我做的全部内容。涉及到了Python爬虫，后端编写，前端编写，数据分析，服务器部署等等。



![image-20220525111605763](C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220525111605763.png)

![image-20220525111625716](C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220525111625716.png)



```python
1.	from flask import Flask, jsonify  
2.	from flask_cors import CORS  
3.	from jieba.analyse import extract_tags  
4.	import string  
5.	import db  
6.	  
7.	  
8.	app = Flask(__name__)  
9.	CORS(app, supports_credentials=True)  
10.	 
11.	@app.route("/map")  
12.	def get_map_data():  
13.	    res = []  
14.	    for tup in db.get_c2_data():  
15.	        # [{'name': '上海', 'value': 318}, {'name': '云南', 'value': 162}]  
16.	        res.append({"name": tup[0], "value": int(tup[1])})  
17.	    return jsonify({"data": res})  
18.	 
19.	 
20.	@app.route("/trend")  
21.	def get_add_trend():  
22.	    data = db.get_add_data()  
23.	    day_ls, confirm_add_ls, suspect_add_ls, heal_add_ls, dead_add_ls = [], [], [], [], []  
24.	    for date, confirm_add, suspect_add, heal_add, dead_add in data:  
25.	        day_ls.append(date.strftime("%m-%d"))  # a是datatime类型  
26.	        confirm_add_ls.append(confirm_add)  
27.	        suspect_add_ls.append(suspect_add)  
28.	        heal_add_ls.append(heal_add)  
29.	        dead_add_ls.append(dead_add)  
30.	  
31.	    return jsonify(  
32.	        {"day": day_ls, "confirm_add_ls": confirm_add_ls, "suspect_add_ls": suspect_add_ls, "heal_add_ls": heal_add_ls,  
33.	         "dead_add_ls": dead_add_ls})  
34.	 
35.	 
36.	@app.route("/shanghai")  
37.	def get_shanghai_data():  
38.	    data = db.get_shanghai_data()  
39.	    day_ls, confirm_add_ls, suspect_add_ls, heal_add_ls, dead_add_ls = [], [], [], [], []  
40.	    for date, a, b, c, d, confirm_add, suspect_add, heal_add, dead_add in data:  
41.	        day_ls.append(date.strftime("%m-%d"))  # a是datatime类型  
42.	        confirm_add_ls.append(confirm_add)  
43.	        suspect_add_ls.append(suspect_add)  
44.	        heal_add_ls.append(heal_add)  
45.	        dead_add_ls.append(dead_add)  
46.	  
47.	    return jsonify(  
48.	        {"day": day_ls, "confirm_add_ls": confirm_add_ls, "suspect_add_ls": suspect_add_ls, "heal_add_ls": heal_add_ls,  
49.	         "dead_add_ls": dead_add_ls})  
50.	  
51.	  
52.	if __name__ == '__main__':  
53.	    app.run(debug=True, port=5000)

```

