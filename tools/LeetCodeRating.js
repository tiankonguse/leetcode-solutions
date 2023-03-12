// ==UserScript== 
// @name         LeetCodeRating｜显示力扣周赛难度分
// @namespace    https://github.com/zhang-wangz
// @version      1.8.10
// @license      MIT
// @description  LeetCodeRating 力扣周赛分数显现，目前支持tag页面,题库页面,company页面,problem_list页面和题目页面
// @author       小东是个阳光蛋(力扣名
// @leetcodehomepage   https://leetcode.cn/u/runonline/
// @homepageURL  https://github.com/zhang-wangz/LeetCodeRating
// @contributionURL https://www.showdoc.com.cn/2069209189620830
// @run-at       document-end
// @match        *://*leetcode.cn/*
// @grant        GM_xmlhttpRequest
// @grant        GM_registerMenuCommand
// @grant        GM_unregisterMenuCommand
// @grant        GM_openInTab
// @grant        GM_notification
// @grant        GM_setValue
// @grant        GM_getValue
// @grant        GM_addStyle
// @grant        GM_getResourceText
// @connect      zerotrac.github.io
// @connect      raw.staticdn.net
// @connect      raw.githubusercontents.com
// @connect      raw.githubusercontent.com
// @require      https://cdn.bootcdn.net/ajax/libs/jquery/3.5.1/jquery.min.js
// @require      https://cdn.bootcdn.net/ajax/libs/layer/3.1.1/layer.min.js
// @grant        unsafeWindow
// @note         2023-03-11 1.1.0 首次自己维护脚本 
// ==/UserScript==

(function () {
    'use strict';

    let version = "1.1.0"


    // 访问相关url
    let teaUrl, versionUrl, sciptUrl, rakingUrl
    teaUrl = "https://raw.githubusercontents.com/zhang-wangz/LeetCodeRating/main/tencentdoc/tea.json"
    versionUrl = "https://raw.githubusercontents.com/zhang-wangz/LeetCodeRating/main/version.json"
    sciptUrl = "https://raw.githubusercontents.com/zhang-wangz/LeetCodeRating/main/leetcodeRating_greasyfork.user.js"
    rakingUrl = "https://raw.githubusercontents.com/zerotrac/leetcode_problem_rating/main/data.json"

    // 页面相关url
    const allUrl = "https://leetcode.cn/problemset/"
    const tagUrl = "https://leetcode.cn/tag/"
    const companyUrl = "https://leetcode.cn/company/"
    const pblistUrl = "https://leetcode.cn/problem-list/"
    const pbUrl = "https://leetcode.cn/problems/"
    const searchUrl = "https://leetcode.cn/search/"

    // req相关url
    const lcnojgo = "https://leetcode.cn/graphql/noj-go"
    const lcgraphql = "https://leetcode.cn/graphql/"
    const chContestUrl = "https://leetcode.cn/contest/"
    const zhContestUrl = "https://leetcode.com/contest/"


    // 用于延时函数的通用id
    let id = ""

    // rank 相关数据
    let t2rate = JSON.parse(GM_getValue("t2ratedb", "{}").toString())
    let latestpb = JSON.parse(GM_getValue("latestpb", "{}").toString())
    let preDate = GM_getValue("preDate", "")

    // 刷新菜单
    Script_setting()
    // urlchange事件
    initUrlChange()

    // 去除复制时候的事件
    if (GM_getValue("switchcopy")) {
        [...document.querySelectorAll('*')].forEach(item => {
            item.oncopy = function (e) {
                e.stopPropagation();
            }
        });
    }

    // 新版本判断
    let isBeta = document.getElementById("__NEXT_DATA__") != undefined

    // 题目提交数据
    let pbSubmissionInfo = JSON.parse(GM_getValue("pbSubmissionInfo", "{}").toString())
    let questiontag = ""
    let updateFlag = false

    // 常量数据
    const dummySend = XMLHttpRequest.prototype.send
    const regPbSubmission = 'https://leetcode.cn/problems/.*/submissions/.*';
    const queryPbSubmission = '\n    query submissionList($offset: Int!, $limit: Int!, $lastKey: String, $questionSlug: String!, $lang: String, $status: SubmissionStatusEnum) {\n  submissionList(\n    offset: $offset\n    limit: $limit\n    lastKey: $lastKey\n    questionSlug: $questionSlug\n    lang: $lang\n    status: $status\n  ) {\n    lastKey\n    hasNext\n    submissions {\n      id\n      title\n      status\n      statusDisplay\n      lang\n      langName: langVerboseName\n      runtime\n      timestamp\n      url\n      isPending\n      memory\n      submissionComment {\n        comment\n      }\n    }\n  }\n}\n    '
    const queryProblemsetQuestionList = `
    query problemsetQuestionList($categorySlug: String, $limit: Int, $skip: Int, $filters: QuestionListFilterInput) {
        problemsetQuestionList(
            categorySlug: $categorySlug
            limit: $limit
            skip: $skip
            filters: $filters
        ) {
            hasMore
            total
            questions {
            acRate
            difficulty
            freqBar
            frontendQuestionId
            isFavor
            paidOnly
            solutionNum
            status
            title
            titleCn
            titleSlug
            topicTags {
                name
                nameTranslated
                id
                slug
            }
            extra {
                hasVideoSolution
                topCompanyTags {
                imgUrl
                slug
                numSubscribed
                }
            }
            }
        }
    }`
    const langMap = {
        "所有语言": null,
        "C++": "cpp",
        "Java": "java",
        "Python": "python",
        "Python3": "python3",
        "MySQL": "mysql",
        "MS SQL Server": "mssql",
        "Oracle": "oraclesql",
        "C": "c",
        "C#": "csharp",
        "JavaScript": "javascript",
        "Ruby": "ruby",
        "Bash": "bash",
        "Swift": "swift",
        "Go": "golang",
        "Scala": "scala",
        "HTML": "html",
        "Python ML": "pythonml",
        "Kotlin": "kotlin",
        "Rust": "rust",
        "PHP": "php",
        "TypeScript": "typescript",
        "Racket": "racket",
        "Erlang": "erlang",
        "Elixir": "elixir",
        "Dart": "dart",
    }
    const statusMap = {
        "所有状态": null,
        "执行通过": "AC",
        "错误解答": "WA",
        "超出内存限制": "MLE",
        "超出输出限制": "OLE",
        "超出时间限制": "TLE",
        "执行出错": "RE",
        "内部出错": "IE",
        "编译出错": "CE",
        "超时": "TO",
    }

    // 如果有数据就会直接初始化，否则初始化为空
    pbSubmissionInfo = JSON.parse(GM_getValue("pbSubmissionInfo", "{}").toString())
    // css1
    $(document.body).append(`<link href="https://cdn.bootcdn.net/ajax/libs/layer/3.1.1/theme/default/layer.min.css" rel="stylesheet">`)


    // 监听urlchange事件定义
    function initUrlChange() {
        let isLoad = false
        const load = () => {
            if (isLoad) return
            isLoad = true

            const oldPushState = history.pushState
            const oldReplaceState = history.replaceState

            history.pushState = function pushState(...args) {
                const res = oldPushState.apply(this, args)
                window.dispatchEvent(new Event('urlchange'))
                return res
            }

            history.replaceState = function replaceState(...args) {
                const res = oldReplaceState.apply(this, args)
                window.dispatchEvent(new Event('urlchange'))
                return res
            }

            window.addEventListener('popstate', () => {
                window.dispatchEvent(new Event('urlchange'))
            })
        }
        return load
    }

    // 菜单方法定义
    function Script_setting() {
        let menu_ALL = [
            ['switchTea', '0x3f tea', '题库页灵茶信息显示', true, true],
            ['switchpbRepo', 'pbRepo function', '题库页评分(不包括灵茶)', true, false],
            ['switchdelvip', 'delvip function', '题库页去除vip加锁题目', false, true],
            ['switchpb', 'pb function', '题目页评分和新版提交信息', true, true],
            ['switchnewBeta', 'new function', '题目页是否使用新版ui', true, true],
            ['switchsearch', 'search function', '题目搜索页评分', true, false],
            ['switchtag', 'tag function', 'tag题单页评分(动态规划等分类题库)', true, false],
            ['switchcompany', 'company function', 'company题单页评分(字节等公司题库)', true, false],
            ['switchpblist', 'pbList function', 'pbList题单页评分', true, false],
            ['switchcopy', 'copy function', '复制去除署名声明(只适用旧版)', true, true],
            ['switchrealoj', 'delvip function', '模拟oj环境(去除通过率,难度,周赛Qidx等)', false, true],
            ['switchperson', 'person function', '纸片人', false, true],
        ], menu_ID = [], menu_ID_Content = [];
        for (const element of menu_ALL) { // 如果读取到的值为 null 就写入默认值
            if (GM_getValue(element[0]) == null) { GM_setValue(element[0], element[3]) };
        }
        registerMenuCommand();

        // 注册脚本菜单
        function registerMenuCommand() {
            if (menu_ID.length > menu_ALL.length) { // 如果菜单ID数组多于菜单数组，说明不是首次添加菜单，需要卸载所有脚本菜单
                for (const element of menu_ID) {
                    GM_unregisterMenuCommand(element);
                }
            }
            for (let i = 0; i < menu_ALL.length; i++) { // 循环注册脚本菜单
                menu_ALL[i][3] = GM_getValue(menu_ALL[i][0]);
                let content = `${menu_ALL[i][3] ? '✅' : '❎'} ${menu_ALL[i][2]}`
                menu_ID[i] = GM_registerMenuCommand(content, function () { menu_switch(`${menu_ALL[i][0]}`, `${menu_ALL[i][1]}`, `${menu_ALL[i][2]}`, `${menu_ALL[i][3]}`) });
                menu_ID_Content[i] = content
            }
            menu_ID[menu_ID.length] = GM_registerMenuCommand(`🏁 当前版本 ${version}`, function () { window.GM_openInTab('https://greasyfork.org/zh-CN/scripts/450890-leetcoderating-%E6%98%BE%E7%A4%BA%E5%8A%9B%E6%89%A3%E5%91%A8%E8%B5%9B%E9%9A%BE%E5%BA%A6%E5%88%86', { active: true, insert: true, setParent: true }); });
            menu_ID_Content[menu_ID_Content.length] = `🏁 当前版本 ${version}`
        }

        //切换选项
        function menu_switch(name, ename, cname, value) {
            if (value == 'false') {
                GM_setValue(`${name}`, true);
                registerMenuCommand(); // 重新注册脚本菜单
                location.reload(); // 刷新网页
                GM_notification({ text: `「${cname}」已开启\n`, timeout: 3500 }); // 提示消息
            } else {
                GM_setValue(`${name}`, false);
                registerMenuCommand(); // 重新注册脚本菜单
                location.reload(); // 刷新网页
                GM_notification({ text: `「${cname}」已关闭\n`, timeout: 3500 }); // 提示消息
            }
            registerMenuCommand(); // 重新注册脚本菜单
        }
    }

    let ajaxReq = (type, reqUrl, headers, data, successFuc) => {
        $.ajax({
            // 请求方式
            type: type,
            // 请求的媒体类型
            contentType: "application/json;charset=UTF-8",
            // 请求地址
            url: reqUrl,
            // 数据，json字符串
            data: JSON.stringify(data),
            // 同步方式
            async: false,
            xhrFields: {
                withCredentials: true
            },
            headers: headers,
            // 请求成功
            success: function (result) {
                successFuc(result)
            },
            // 请求失败，包含具体的错误信息
            error: function (e) {
                console.log(e.status);
                console.log(e.responseText);
            }
        });
    }


    // lc 基础req
    let baseReq = (type, reqUrl, query, variables, successFuc) => {
        //请求参数
        let list = { "query": query, "variables": variables };
        //
        ajaxReq(type, reqUrl, null, list, successFuc)

    };

    // post请求
    let postReq = (reqUrl, query, variables, successFuc) => {
        baseReq("POST", reqUrl, query, variables, successFuc)
    }

    let newbtnSwitch = () => {
        let headers = {
            accept: '*/*',
            'accept-language': 'zh-CN,zh;q=0.9,zh-TW;q=0.8,en;q=0.7',
            'content-type': 'application/json',
        }
        let body = {
            operationName: 'setQdToBeta',
            variables: {},
            query: /* GraphQL */ `
            mutation setQdToBeta {
                authenticationSetBetaParticipation(
                participationType: NEW_QUESTION_DETAIL_PAGE
                optedIn: true
                ) {
                inBeta
                hitBeta
                __typename
                }
            }
            `,
        }
        ajaxReq("POST", lcnojgo, headers, body, () => { })
    }

    newbtnSwitch()


    // 修改参数
    let submissionLst = []
    let next = true

    // 深拷贝
    function deepclone(obj) {
        let str = JSON.stringify(obj);
        return JSON.parse(str);
    }

    // 获取数字
    function getcontestNumber(url) {
        return parseInt(url.substr(15));
    }

    // 获取时间
    function getCurrentDate(format) {
        let now = new Date();
        let year = now.getFullYear(); //得到年份
        let month = now.getMonth(); //得到月份
        let date = now.getDate(); //得到日期
        let hour = now.getHours(); //得到小时
        let minu = now.getMinutes(); //得到分钟
        let sec = now.getSeconds(); //得到秒
        month = month + 1;
        if (month < 10) month = "0" + month;
        if (date < 10) date = "0" + date;
        if (hour < 10) hour = "0" + hour;
        if (minu < 10) minu = "0" + minu;
        if (sec < 10) sec = "0" + sec;
        let time = "";
        // 精确到天
        if (format == 1) {
            time = year + "年" + month + "月" + date + "日";
        }
        // 精确到分
        else if (format == 2) {
            time = year + "-" + month + "-" + date + " " + hour + ":" + minu + ":" + sec;
        }
        return time;
    }

    GM_addStyle(`
        .containerlingtea {
            background: rgba(233, 183, 33, 0.2);
            white-space: pre-wrap;
            word-wrap: break-word;
            display: block;
        }
    `)

    function checksolve() {
        layer.open({
            type: 1 // Page 层类型
            , area: ['650px', '450px']
            , title: '题解说明'
            , shade: 0.6 // 遮罩透明度
            , maxmin: true // 允许全屏最小化
            , anim: 5 // 0-6的动画形式，-1不开启
            , content: `<pre class="containerlingtea" style="padding:20px;color:#000;">${latestpb["solve"]['str']}</pre>`
        });
    }

    function checkout() {
        layer.open({
            type: 1 // Page 层类型
            , area: ['650px', '450px']
            , title: '输入/输出'
            , shade: 0.6 // 遮罩透明度
            , maxmin: true // 允许全屏最小化
            , anim: 5 // 0-6的动画形式，-1不开启
            , content: `<pre class="containerlingtea" style="padding:20px;color:#000;">${latestpb["out"]["str"]}</pre>`
        });
    }

    function checktrans() {
        latestpb["pb"]["str"] = latestpb["pb"]["str"].replace('<', "&lt;").replace('>', "&gt;")
        layer.open({
            type: 0
            , area: ['650px', '450px']
            , title: '中文翻译'
            , shade: 0.6 // 遮罩透明度
            , maxmin: true // 允许全屏最小化
            , anim: 5 // 0-6的动画形式，-1不开启
            , content: `<pre class="containerlingtea" style="padding:20px;color:#000;">${latestpb["pb"]["str"]}</pre>`
        });
    }


    // 因为力扣未捕获错误信息，所以重写一下removechild方法
    const removeChildFn = Node.prototype.removeChild;
    Node.prototype.removeChild = function (n) {
        let err = null;
        try {
            err = removeChildFn.call(this, n); // 正常删除
        } catch (error) {
            if (!error.toString().includes("NotFoundError")) console.log("力扣api发生错误: ", error.toString().substr(0, 150))
        }
        return err
    }

    // window.onerror = function(message, source, lineno, colno, error) {
    //     message.preventDefault()
    //     console.log("力扣api发生错误:", message.message)
    //     return true
    // }

    function callback(tag, variables) {
        let data;
        if (tag == 'query problemsetQuestionList') {
            postReq(lcgraphql, queryProblemsetQuestionList, variables, (res) => {
                res.data.problemsetQuestionList.questions = res.data.problemsetQuestionList.questions.filter(e => !e.paidOnly)
                data = res
            })
        }
        return data
    }

    // 写一个拦截题库页面的工具
    const originalOpen = XMLHttpRequest.prototype.open
    function intercept() {
        XMLHttpRequest.prototype.open = function newOpen(method, url, async, user, password, disbaleIntercept) {
            if (!disbaleIntercept && method.toLocaleLowerCase() === 'post' && url === `/graphql/`) {
                const originalSend = this.send
                this.send = async str => {
                    try {
                        if (typeof str === 'string') {
                            let tag
                            const body = JSON.parse(str)
                            if (body.query && body.query.includes('query problemsetQuestionList')) {
                                tag = 'query problemsetQuestionList'
                                for (const key of ['response', 'responseText']) {
                                    Object.defineProperty(this, key, {
                                        get: function () {
                                            const data = callback(tag, body.variables)
                                            return JSON.stringify(data)
                                        },
                                        configurable: true,
                                    })
                                }
                            }
                            str = JSON.stringify(body)
                        }
                    } catch (error) {
                        console.log(error)
                    }
                    return originalSend.call(this, str)
                }
            }
            originalOpen.apply(this, [method, url, async, user, password])
        }
    }

    function restore() {
        XMLHttpRequest.prototype.open = originalOpen
    }

    if (GM_getValue("switchdelvip")) intercept(); else restore()


    let t1, le // pb
    let tFirst, tLast  // all
    function getData() {
        let switchpbRepo = GM_getValue("switchpbRepo")
        let switchTea = GM_getValue("switchTea")
        let switchrealoj = GM_getValue("switchrealoj")
        try {
            let arr = document.querySelector("div[role='rowgroup']")
            // pb页面加载时直接返回
            if (arr == undefined) {
                return
            }

            let head = document.querySelector("#__next > div > div > div.grid.grid-cols-4.gap-4.md\\:grid-cols-3.lg\\:grid-cols-4.lg\\:gap-6 > div.col-span-4.z-base.md\\:col-span-2.lg\\:col-span-3 > div.relative.flex.items-center.space-x-4.py-3.my-4.-ml-4.overflow-hidden.pl-4")
            let l = head.childNodes.length
            let lasthead = head.lastChild
            let lastchild = arr.lastChild
            // 防止过多的无效操作
            let first = switchTea ? 1 : 0
            if ((!switchpbRepo || (tFirst != undefined && tFirst == arr.childNodes[first].innerHTML && tLast != undefined && tLast == lastchild.innerHTML))
                && (!switchTea || (lasthead.childNodes[0].childNodes[1] instanceof Text && lasthead.childNodes[0].childNodes[1].textContent == "灵茶の试炼"))
                && (!switchrealoj) || lastchild.childNodes[4].textContent == "隐藏") {
                return
            }

            t2rate = JSON.parse(GM_getValue("t2ratedb", "{}").toString())
            latestpb = JSON.parse(GM_getValue("latestpb", "{}").toString())

            // 灵茶题目渲染
            if (switchTea) {
                if (arr.childNodes[0].childNodes[2].textContent != "题解") {
                    let div = document.createElement('div')
                    div.setAttribute("role", "row")
                    div.setAttribute("style", "display:flex;flex:1 0 auto;min-width:0px")
                    div.setAttribute("class", "odd:bg-layer-1 even:bg-overlay-1 dark:odd:bg-dark-layer-bg dark:even:bg-dark-fill-4")
                    let teaUrl = latestpb["url"]["url"]
                    let vo = ['cf题目', 'atcoder']
                    let lst = ['codeforces', 'atcoder']
                    let src = "未知来源";
                    for (let index = 0; index < lst.length; index++) {
                        const element = lst[index];
                        if (teaUrl.includes(element)) {
                            src = vo[index]
                            break
                        }
                    }
                    latestpb['nd']['str'] = latestpb['nd']['str'] !== '' ? latestpb['nd']['str'].substr(0, 4) : "未知"
                    div.innerHTML += `<div role="cell" style="box-sizing:border-box;flex:60 0 auto;min-width:0px;width:60px" class="mx-2 py-[11px]">${src}</div>`
                    if (teaUrl != "") {
                        div.innerHTML += `<div role="cell" style="box-sizing:border-box;flex:160 0 auto;min-width:0px;width:160px" class="mx-2 py-[11px]"><div class="max-w-[302px] flex items-center"><div class="overflow-hidden"><div class="flex items-center"><div class="truncate overflow-hidden"><a href="${latestpb["url"]["url"]}"  target="_blank" class="h-5 hover:text-blue-s dark:hover:text-dark-blue-s">${latestpb["date"]["str"]}&nbsp灵茶</a></div></div></div></div></div>`
                    } else {
                        div.innerHTML += `<div role="cell" style="box-sizing:border-box;flex:160 0 auto;min-width:0px;width:160px" class="mx-2 py-[11px]"><div class="max-w-[302px] flex items-center"><div class="overflow-hidden"><div class="flex items-center"><div class="truncate overflow-hidden"><p class="h-5">${latestpb["date"]["str"]}&nbsp灵茶</p></div></div></div></div></div>`
                    }
                    div.innerHTML += `<div role="cell" style="box-sizing:border-box;flex:96 0 auto;min-width:0px;width:96px" class="mx-2 py-[11px]"><span class="flex items-center space-x-2 text-label-1 dark:text-dark-label-1"><a href="javascript:;" class="truncate" aria-label="solution">题解</a></span></div><div \
                        role="cell" style="box-sizing:border-box;flex:82 0 auto;min-width:0px;width:82px" class="mx-2 py-[11px]"><span><a href="javascript:;" class="truncate" aria-label="solution">输入/输出</a></span></div><div \
                        role="cell" style="box-sizing:border-box;flex:60 0 auto;min-width:0px;width:60px" class="mx-2 py-[11px]"><span class="text-purple dark:text-dark-purple">${latestpb['nd']['str']}</span></div><div \
                        role="cell" style="box-sizing:border-box;flex:88 0 auto;min-width:0px;width:88px" class="mx-2 py-[11px]"><span><a href="javascript:;" >中文翻译</a></span></div>`

                    div.childNodes[2].addEventListener("click", (e) => {
                        e.preventDefault();
                        checksolve();
                    });
                    div.childNodes[3].addEventListener("click", (e) => {
                        e.preventDefault();
                        checkout();
                    })
                    div.childNodes[5].addEventListener("click", (e) => {
                        e.preventDefault();
                        checktrans();
                    })
                    arr.insertBefore(div, arr.childNodes[0])
                }
            }

            // console.log(tFirst)
            // console.log(tLast)
            if (switchpbRepo) {
                let allpbHead = document.querySelector("div[role='row']")
                let rateRefresh = false
                let headndidx, acrateidx
                let i = 0
                allpbHead.childNodes.forEach(e => {
                    if (e.textContent.includes("难度")) {
                        headndidx = i
                    }
                    if (e.textContent.includes("通过率")) {
                        acrateidx = i
                    }
                    if (e.textContent.includes("题目评分")) {
                        rateRefresh = true
                    }
                    i += 1
                })
                // console.log(pbtitleidx)
                let childs = arr.childNodes
                let idx = switchTea ? 1 : 0
                let childLength = childs.length
                for (; idx < childLength; idx++) {
                    let v = childs[idx]
                    let t = v.childNodes[1].textContent
                    // console.log(t)
                    let data = t.split(".")
                    let id = data[0].trim()
                    let nd = v.childNodes[headndidx].childNodes[0].innerHTML
                    if (switchrealoj) {
                        v.childNodes[acrateidx].textContent = "隐藏"
                        v.childNodes[headndidx].textContent = "隐藏"
                        continue
                    }
                    if (t2rate[id] != undefined && !rateRefresh) {
                        nd = t2rate[id]["Rating"]
                        // console.log(nd)
                        v.childNodes[headndidx].childNodes[0].innerHTML = nd
                    } else {
                        let nd2ch = { "text-olive dark:text-dark-olive": "简单", "text-yellow dark:text-dark-yellow": "中等", "text-pink dark:text-dark-pink": "困难" }
                        let cls = v.childNodes[headndidx].childNodes[0].getAttribute("class")
                        v.childNodes[headndidx].childNodes[0].innerHTML = nd2ch[cls]
                    }
                }
                tFirst = arr.childNodes[first].innerHTML
                tLast = lastchild.innerHTML
            }
        } catch (e) {
            return
        }
    }

    let tagt;
    function getTagData() {
        if (!GM_getValue("switchtag")) return;
        try {
            // 筛选更新
            let arr = document.querySelector(".ant-table-tbody")
            let head = document.querySelector(".ant-table-cell").parentNode
            if (tagt != undefined && tagt == arr.lastChild.innerHTML) {
                return
            }
            let rateRefresh = false
            // 确认难度序列
            let headndidx
            for (let i = 0; i < head.childNodes.length; i++) {
                let headEle = head.childNodes[i]
                // console.log(headEle.textContent)
                if (headEle.textContent.includes("难度")) {
                    headndidx = i
                }
                if (headEle.textContent.includes("题目评分")) {
                    rateRefresh = true
                }
            }
            let childs = arr.childNodes
            for (const element of childs) {
                let v = element
                let t = v.childNodes[1].textContent
                let data = t.split(".")
                let id = data[0].trim()
                let nd = v.childNodes[headndidx].childNodes[0].innerHTML
                if (t2rate[id] != undefined && !rateRefresh) {
                    nd = t2rate[id]["Rating"]
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd
                } else {
                    let nd2ch = { "rgba(var(--dsw-difficulty-easy-rgb), 1)": "简单", "rgba(var(--dsw-difficulty-medium-rgb), 1)": "中等", "rgba(var(--dsw-difficulty-hard-rgb), 1)": "困难" }
                    let clr = v.childNodes[headndidx].childNodes[0].getAttribute("color")
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd2ch[clr]
                }
            }
            tagt = arr.lastChild.innerHTML
        } catch (e) {
            return
        }
    }

    let companyt;
    function getCompanyData() {
        if (!GM_getValue("switchcompany")) return;
        try {
            let arr = document.querySelector(".ant-table-tbody")
            let head = document.querySelector(".ant-table-cell").parentNode
            if (companyt != undefined && companyt == arr.lastChild.innerHTML) {
                return
            }
            // 确认难度序列
            let rateRefresh = false
            let headndidx
            for (let i = 0; i < head.childNodes.length; i++) {
                let headEle = head.childNodes[i]
                if (headEle.textContent.includes("难度")) {
                    headndidx = i
                }
                if (headEle.textContent.includes("题目评分")) {
                    rateRefresh = true
                }
            }
            let childs = arr.childNodes
            for (const element of childs) {
                let v = element
                let t = v.childNodes[1].textContent
                let data = t.split(".")
                let id = data[0].trim()
                let nd = v.childNodes[headndidx].childNodes[0].innerHTML
                if (t2rate[id] != undefined && !rateRefresh) {
                    nd = t2rate[id]["Rating"]
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd
                } else {
                    let nd2ch = { "rgba(var(--dsw-difficulty-easy-rgb), 1)": "简单", "rgba(var(--dsw-difficulty-medium-rgb), 1)": "中等", "rgba(var(--dsw-difficulty-hard-rgb), 1)": "困难" }
                    let clr = v.childNodes[headndidx].childNodes[0].getAttribute("color")
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd2ch[clr]
                }
            }
            companyt = arr.lastChild.innerHTML
        } catch (e) {
            return
        }
    }

    let pblistt;
    function getPblistData() {
        if (!GM_getValue("switchpblist")) return;
        try {
            let arr = document.querySelector("div[role='rowgroup']")
            if (arr == undefined) return
            if (pblistt != undefined && pblistt == arr.lastChild.innerHTML) {
                return
            }

            let head = document.querySelector("div[role='row']")
            // 确认难度序列
            let rateRefresh = false
            let headndidx;
            for (let i = 0; i < head.childNodes.length; i++) {
                let headEle = head.childNodes[i]
                if (headEle.textContent.includes("难度")) {
                    headndidx = i
                }
                if (headEle.textContent.includes("题目评分")) {
                    rateRefresh = true
                }
            }
            let childs = arr.childNodes
            for (const element of childs) {
                let v = element
                let t = v.childNodes[1].textContent
                let data = t.split(".")
                let id = data[0].trim()
                let nd = v.childNodes[headndidx].childNodes[0].innerHTML
                if (t2rate[id] != undefined && !rateRefresh) {
                    nd = t2rate[id]["Rating"]
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd
                } else {
                    let nd2ch = { "text-olive dark:text-dark-olive": "简单", "text-yellow dark:text-dark-yellow": "中等", "text-pink dark:text-dark-pink": "困难" }
                    let cls = v.childNodes[headndidx].childNodes[0].getAttribute("class")
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd2ch[cls]
                }
            }
            pblistt = arr.lastChild.innerHTML
        } catch (e) {
            return
        }
    }

    function getSearch() {
        if (!GM_getValue("switchsearch")) return
        try {
            let arr = $("div[role='table']")
            if (arr.length == 0) return
            arr = arr[0].childNodes[1]

            let head = document.querySelector("div[role='row']")
            // 确认难度序列
            let rateRefresh = false
            let headndidx
            for (let i = 0; i < head.childNodes.length; i++) {
                let headEle = head.childNodes[i]
                if (headEle.textContent.includes("难度")) {
                    headndidx = i
                }
                if (headEle.textContent.includes("题目评分")) {
                    rateRefresh = true
                }
            }

            let childs = arr.childNodes
            for (const element of childs) {
                let v = element
                // let length = v.childNodes.length
                let t = v.childNodes[1].textContent
                let data = t.split(".")
                let id = data[0].trim()
                let nd = v.childNodes[headndidx].childNodes[0].innerHTML
                if (t2rate[id] != undefined && !rateRefresh) {
                    nd = t2rate[id]["Rating"]
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd
                } else {
                    let nd2ch = { "text-green-s": "简单", "text-yellow": "中等", "text-red-s": "困难" }
                    let clr = v.childNodes[headndidx].childNodes[0].getAttribute("class")
                    v.childNodes[headndidx].childNodes[0].innerHTML = nd2ch[clr]
                }
            }
        } catch (e) {
            return
        }
    }
    let clickFlag = true
    let startTime, endTime
    let newisaddBtnClick = () => {
        if (!clickFlag) return
        GM_setValue("switchnewBeta", true)
        newbtnSwitch()
        location.reload()
    }

    function moveSupport(selector) {
        // 拖动
        let _move = false;
        let ismove = false; // 移动标记
        let _x, _y; // 鼠标离控件左上角的相对位置
        jQuery(document).ready(function ($) {
            $(selector).mousedown(function (e) {
                _move = true;
                startTime = new Date().getTime();
                _x = e.pageX - parseInt($(selector).css("left"));
                _y = e.pageY - parseInt($(selector).css("top"));
            });
            $(document).mousemove(function (e) {
                if (_move) {
                    let x = e.pageX - _x;
                    let y = e.pageY - _y;
                    let wx = $(window).width() - $(selector).width();
                    let dy = $(document).height() - $(selector).height();
                    if (x >= 0 && x <= wx && y > 0 && y <= dy) {
                        $(selector).css({
                            top: y,
                            left: x
                        }); //控件新位置
                        ismove = true;
                    }
                }
            }).mouseup(function () {
                endTime = new Date().getTime();
                clickFlag = endTime - startTime < 200;
                _move = false;
            });
        });
    }


    function switchUi() {
        // 新版按钮切换
        let newcopyBtn = document.querySelector("[name='newisaddBtn']")
        let newBtn = document.querySelector(".css-h6vf0p-card-Box")
        if (newcopyBtn) {
            // paas
        } else if (newBtn && newBtn.getAttribute("hidden") == null) {
            let cloneBtn = newBtn.cloneNode()
            cloneBtn.textContent = newBtn.textContent
            newBtn.setAttribute("hidden", "true")
            newBtn.parentNode.appendChild(cloneBtn)

            cloneBtn.setAttribute("name", "newisaddBtn")
            cloneBtn.addEventListener('click', newisaddBtnClick)
            moveSupport("[name='newisaddBtn']")
        }

        let oldBtn = document.querySelector("#editor > div.absolute.right-\\[25px\\].bottom-\\[84px\\].z-overlay > div")
        if (oldBtn) {
            if (oldBtn.getAttribute("name") && oldBtn.getAttribute("name").includes("isaddBtn")) {
                // paas
            } else {
                // console.log(oldBtn.getAttribute("name"))
                oldBtn.setAttribute("name", "isaddBtn")
                oldBtn.addEventListener('click', () => {
                    GM_setValue("switchnewBeta", false)
                })
            }
        }
    }

    function getSubmitBtn(isBeta) {
        if (!isBeta) {
            let subBtn = $(".submit__-6u9")
            return subBtn
        } else {
            return $("button[class='px-3 py-1.5 font-medium items-center whitespace-nowrap transition-all focus:outline-none inline-flex text-label-r bg-green-s dark:bg-dark-green-s hover:bg-green-3 dark:hover:bg-dark-green-3 rounded-lg']")
        }
    }

    function getpb() {
        if (!GM_getValue("switchpb")) return
        let switchrealoj = GM_getValue("switchrealoj")
        // 是否在提交页面
        let statusEle = window.location.href.match(regPbSubmission)
        if (isBeta) {
            if (!window.location.href.startsWith(pbUrl)) questiontag = ""
            if (statusEle) {
                let submissionUrl = window.location.href
                let data = submissionUrl.split("/")
                questiontag = data[data.length - 3]
                if (data[data.length - 2] != "submissions") questiontag = data[data.length - 4]
                let statusOrlangPa = document.querySelector("#qd-content > div.h-full.flex-col.ssg__qd-splitter-primary-w > div > div > div > div.flex.h-full.w-full.overflow-y-auto > div > div.sticky.top-0.w-full.bg-layer-1.dark\\:bg-dark-layer-1 > div")
                if (statusOrlangPa == undefined) return;
                let statusQus = statusOrlangPa.childNodes[0].childNodes[0].childNodes[0]
                let lang = statusOrlangPa.childNodes[1].childNodes[0].childNodes[0]
                if (lang == undefined || statusQus == undefined) return;
                updateSubmissionLst(statusEle, questiontag, lang.innerText, statusQus.innerText);
                return;
            }
        }
        // 切换onclik
        switchUi()

        // 题目页面
        try {
            // 旧版的标题位置
            let t = document.querySelector("#question-detail-main-tabs > div.css-1qqaagl-layer1.css-12hreja-TabContent.e16udao5 > div > div.css-xfm0cl-Container.eugt34i0 > h4 > a")
            if (t == undefined) {
                // 新版逻辑
                t = document.querySelector("#qd-content > div.h-full.flex-col.ssg__qd-splitter-primary-w > div > div > div > div.flex.h-full.w-full.overflow-y-auto > div > div > div.w-full.px-5.pt-4 > div > div:nth-child(1) > div.flex-1 > div > div > span")
                if (t == undefined) {
                    t1 = "unknown"
                    return
                }
                let data = t.innerText.split(".")
                let id = data[0].trim()
                let colorSpan = document.querySelector("#qd-content > div.h-full.flex-col.ssg__qd-splitter-primary-w > div > div > div > div.flex.h-full.w-full.overflow-y-auto > div > div > div.w-full.px-5.pt-4 > div > div.mt-3.flex.space-x-4 > div:nth-child(1)")
                let pa = colorSpan.parentNode
                if (t1 != undefined && t1 == id) {
                    return
                }
                // 新版统计难度分数并且修改
                let nd = colorSpan.getAttribute("class")
                let nd2ch = { "text-olive dark:text-dark-olive": "简单", "text-yellow dark:text-dark-yellow": "中等", "text-pink dark:text-dark-pink": "困难" }
                if (switchrealoj || (t2rate[id] != undefined)) {
                    if (switchrealoj) colorSpan.remove()
                    else if (t2rate[id] != undefined) colorSpan.innerHTML = t2rate[id]["Rating"]
                } else {
                    for (let item in nd2ch) {
                        if (nd.toString().includes(item)) {
                            colorSpan.innerHTML = nd2ch[item]
                            break
                        }
                    }
                }
                // 新版逻辑，准备做周赛链接,如果已经不存在组件就执行操作
                let url = chContestUrl
                let zhUrl = zhContestUrl
                let q = pa.lastChild
                let le = pa.childNodes.length
                if (q.textContent == "") {
                    let abody = document.createElement("a")
                    abody.setAttribute("data-small-spacing", "true")
                    abody.setAttribute("class", "css-nabodd-Button e167268t1")

                    let abody2 = document.createElement("a")
                    abody2.setAttribute("data-small-spacing", "true")
                    abody2.setAttribute("class", "css-nabodd-Button e167268t1")

                    let span = document.createElement("span")
                    let span2 = document.createElement("span")
                    // ContestID_zh  ContestSlug
                    if (t2rate[id] != undefined) {
                        let contestUrl;
                        let num = getcontestNumber(t2rate[id]["ContestSlug"])
                        if (num < 83) { contestUrl = zhUrl } else { contestUrl = url }
                        span.innerText = t2rate[id]["ContestID_zh"]
                        span2.innerText = t2rate[id]["ProblemIndex"]

                        abody.setAttribute("href", contestUrl + t2rate[id]["ContestSlug"])
                        abody.setAttribute("target", "_blank")
                        abody.removeAttribute("hidden")

                        abody2.setAttribute("href", contestUrl + t2rate[id]["ContestSlug"] + "/problems/" + t2rate[id]["TitleSlug"])
                        abody2.setAttribute("target", "_blank")
                        if (switchrealoj) abody2.setAttribute("hidden", true)
                        else abody2.removeAttribute("hidden")
                    } else {
                        span.innerText = "对应周赛未知"
                        abody.setAttribute("href", "")
                        abody.setAttribute("target", "_self")
                        abody.setAttribute("hidden", "true")

                        span2.innerText = "未知"
                        abody2.setAttribute("href", "")
                        abody2.setAttribute("target", "_self")
                        abody2.setAttribute("hidden", "true")
                    }
                    abody.appendChild(span)
                    abody2.appendChild(span2)
                    pa.appendChild(abody)
                    pa.appendChild(abody2)
                } else if (q.textContent.charAt(0) == "Q" || q.textContent == "未知") {  // 存在就直接替换
                    if (t2rate[id] != undefined) {
                        let contestUrl;
                        let num = getcontestNumber(t2rate[id]["ContestSlug"])
                        if (num < 83) { contestUrl = zhUrl } else { contestUrl = url }
                        pa.childNodes[le - 2].childNodes[0].innerText = t2rate[id]["ContestID_zh"]
                        pa.childNodes[le - 2].setAttribute("href", contestUrl + t2rate[id]["ContestSlug"])
                        pa.childNodes[le - 2].setAttribute("target", "_blank")
                        pa.childNodes[le - 2].removeAttribute("hidden")

                        pa.childNodes[le - 1].childNodes[0].innerText = t2rate[id]["ProblemIndex"]
                        pa.childNodes[le - 1].setAttribute("href", contestUrl + t2rate[id]["ContestSlug"] + "/problems/" + t2rate[id]["TitleSlug"])
                        pa.childNodes[le - 1].setAttribute("target", "_blank")
                        if (switchrealoj) pa.childNodes[le - 1].setAttribute("hidden", "true")
                        else pa.childNodes[le - 1].removeAttribute("hidden")
                    } else {
                        pa.childNodes[le - 2].childNodes[0].innerText = "对应周赛未知"
                        pa.childNodes[le - 2].setAttribute("href", "")
                        pa.childNodes[le - 2].setAttribute("target", "_self")
                        pa.childNodes[le - 2].setAttribute("hidden", "true")

                        pa.childNodes[le - 1].childNodes[0].innerText = "未知"
                        pa.childNodes[le - 1].setAttribute("href", "")
                        pa.childNodes[le - 1].setAttribute("target", "_self")
                        pa.childNodes[le - 1].setAttribute("hidden", "true")
                    }
                }
                t1 = id

            } else {
                // 旧版逻辑，使用参数t和t1，分别代表标题的html和标题id
                // 旧版题目左侧列表里面所有分数
                let pbAll = document.querySelector("body > div.question-picker-detail__2A9V.show__GfjG > div.question-picker-detail-menu__3NQq.show__3hiR > div.lc-theme-dark.question-picker-questions-wrapper__13qM > div")
                if (pbAll != undefined) {
                    let childs = pbAll.childNodes
                    for (const element of childs) {
                        let v = element
                        let length = v.childNodes.length
                        let t = v.childNodes[0].childNodes[1].innerText
                        let data = t.split(" ")[0]
                        let id = data.slice(1)
                        let nd = v.childNodes[length - 1].childNodes[0].innerText
                        if (t2rate[id] != undefined) {
                            nd = t2rate[id]["Rating"]
                            v.childNodes[length - 1].childNodes[0].innerText = nd
                        }
                    }
                }
                // 旧版标题修改位置
                let data = t.innerText.split(".")
                let id = data[0].trim()
                let ndtext = document.querySelector("#question-detail-main-tabs > div.css-1qqaagl-layer1.css-12hreja-TabContent.e16udao5 > div > div.css-xfm0cl-Container.eugt34i0 > div > span:nth-child(1)")
                let colorSpan = document.querySelector("#question-detail-main-tabs > div.css-1qqaagl-layer1.css-12hreja-TabContent.e16udao5 > div > div.css-xfm0cl-Container.eugt34i0 > div > span:nth-child(2)")
                let pa = colorSpan.parentNode
                if ((t1 != undefined && t1 == id) && (le != undefined && le <= pa.childNodes.length)) {
                    return
                }
                // 统计难度分数
                let nd = colorSpan.getAttribute("data-degree")
                let nd2ch = { "easy": "简单", "medium": "中等", "hard": "困难" }
                if (switchrealoj || t2rate[id] != undefined) {
                    if (switchrealoj) { colorSpan.remove(); ndtext.remove() }
                    else colorSpan.innerHTML = t2rate[id]["Rating"]
                } else {
                    colorSpan.innerHTML = nd2ch[nd]
                }
                // 准备做周赛链接,如果已经不存在组件就执行操作
                let url = chContestUrl
                let zhUrl = zhContestUrl
                if (le == undefined || le != pa.childNodes.length) {
                    let abody = document.createElement("a")
                    abody.setAttribute("data-small-spacing", "true")
                    abody.setAttribute("class", "css-nabodd-Button e167268t1")

                    let button = document.createElement("button")
                    button.setAttribute("class", "css-nabodd-Button e167268t1")
                    let abody2 = document.createElement("a")
                    abody2.setAttribute("data-small-spacing", "true")
                    abody2.setAttribute("class", "css-nabodd-Button e167268t1")

                    let span = document.createElement("span")
                    let span2 = document.createElement("span")
                    // ContestID_zh  ContestSlug
                    if (t2rate[id] != undefined) {
                        let contestUrl;
                        let num = getcontestNumber(t2rate[id]["ContestSlug"])
                        if (num < 83) { contestUrl = zhUrl } else { contestUrl = url }
                        span.innerText = t2rate[id]["ContestID_zh"]
                        span2.innerText = t2rate[id]["ProblemIndex"]

                        abody.setAttribute("href", contestUrl + t2rate[id]["ContestSlug"])
                        abody.setAttribute("target", "_blank")
                        abody.removeAttribute("hidden")

                        abody2.setAttribute("href", contestUrl + t2rate[id]["ContestSlug"] + "/problems/" + t2rate[id]["TitleSlug"])
                        abody2.setAttribute("target", "_blank")
                        if (switchrealoj) abody2.setAttribute("hidden", "true")
                        else abody2.removeAttribute("hidden")
                    } else {
                        span.innerText = "对应周赛未知"
                        abody.setAttribute("href", "")
                        abody.setAttribute("target", "_self")
                        abody.setAttribute("hidden", "true")

                        span2.innerText = "未知"
                        abody2.setAttribute("href", "")
                        abody2.setAttribute("target", "_self")
                        abody2.setAttribute("hidden", "true")
                    }
                    abody.appendChild(span)
                    abody2.appendChild(span2)
                    button.appendChild(abody2)
                    pa.appendChild(abody)
                    pa.appendChild(button)
                } else if (le == pa.childNodes.length) {  // 存在就直接替换
                    if (t2rate[id] != undefined) {
                        let contestUrl;
                        let num = getcontestNumber(t2rate[id]["ContestSlug"])
                        if (num < 83) { contestUrl = zhUrl } else { contestUrl = url }
                        pa.childNodes[le - 2].childNodes[0].innerText = t2rate[id]["ContestID_zh"]
                        pa.childNodes[le - 2].setAttribute("href", contestUrl + t2rate[id]["ContestSlug"])
                        pa.childNodes[le - 2].setAttribute("target", "_blank")
                        pa.childNodes[le - 2].removeAttribute("hidden")

                        pa.childNodes[le - 1].childNodes[0].childNodes[0].innerText = t2rate[id]["ProblemIndex"]
                        pa.childNodes[le - 1].childNodes[0].setAttribute("href", contestUrl + t2rate[id]["ContestSlug"] + "/problems/" + t2rate[id]["TitleSlug"])
                        pa.childNodes[le - 1].childNodes[0].setAttribute("target", "_blank")
                        if (switchrealoj) pa.childNodes[le - 1].setAttribute("hidden", "true")
                        else pa.childNodes[le - 1].childNodes[0].removeAttribute("hidden")
                    } else {
                        pa.childNodes[le - 2].childNodes[0].innerText = "对应周赛未知"
                        pa.childNodes[le - 2].setAttribute("href", "")
                        pa.childNodes[le - 2].setAttribute("target", "_self")
                        pa.childNodes[le - 2].setAttribute("hidden", "true")

                        pa.childNodes[le - 1].childNodes[0].childNodes[0].innerText = "未知"
                        pa.childNodes[le - 1].childNodes[0].setAttribute("href", "")
                        pa.childNodes[le - 1].childNodes[0].setAttribute("target", "_self")
                        pa.childNodes[le - 1].childNodes[0].setAttribute("hidden", "true")
                    }
                }
                le = pa.childNodes.length
                t1 = id
            }
        } catch (e) {
            return
        }
    }

    // 查询提交更新信息并保存到内存中
    let QuerySubmissionUpdate = (questiontag, lang, statusQus) => {
        let key = questiontag + langMap[lang] + statusMap[statusQus]
        pbSubmissionInfo = JSON.parse(GM_getValue("pbSubmissionInfo", "{}").toString())
        let saveData = (key, lst) => {
            pbSubmissionInfo[key] = lst
            GM_setValue("pbSubmissionInfo", JSON.stringify(pbSubmissionInfo))
        }

        let successFuc = (res) => {
            let data = res.data.submissionList
            let submissions = data.submissions
            next = deepclone(data.hasNext)
            // console.log("req success: ", data)
            submissionLst = submissionLst.concat(submissions)
            saveData(key, submissionLst)
            console.log("update submission data: ", questiontag, langMap[lang], statusMap[statusQus])
        }
        var variables = {
            "questionSlug": questiontag,
            "offset": 0,
            "limit": 40,
            "lastKey": null,
            "status": null,
            "lang": langMap[lang],
            "status": statusMap[statusQus],
        };
        next = true
        submissionLst = []
        // 调试使用
        // let cnt = 0
        while (next) {
            postReq(lcgraphql, queryPbSubmission, variables, successFuc)
            variables.offset += 40
            // cnt += 1
            // console.log("第" + cnt + "步")
        }
    }
    // 监听
    let addListener = () => {
        // console.log("addListener....")
        XMLHttpRequest.prototype.send = function (str) {
            const _onreadystatechange = this.onreadystatechange;
            this.onreadystatechange = (...args) => {
                if (this.readyState === this.DONE && this.responseURL.startsWith(lcnojgo)) {
                    if (this.status === 200 || this.response.type === "application/json") {
                        // console.log("update list....")
                        if (window.location.href.startsWith(pbUrl)) updateFlag = true
                    }
                }
                if (_onreadystatechange) {
                    _onreadystatechange.apply(this, args);
                }
            }
            return dummySend.call(this, str);
        }
    }
    addListener()

    // 更新提交页数据列表
    let updateSubmissionLst = (statusEle, questiontag, lang, statusQus) => {
        // 数据替换操作
        try {
            let key = questiontag + langMap[lang] + statusMap[statusQus]
            if (questiontag != "" && statusEle) {
                let arr = document.querySelector("#qd-content > div.h-full.flex-col.ssg__qd-splitter-primary-w > div > div > div > div.flex.h-full.w-full.overflow-y-auto > div > div.h-full.w-full")
                if (arr == undefined) return
                let childs = arr.childNodes
                if (childs.length == 1 || childs.length == 0) return;

                // 已经替换过就直接返回
                let lastNode = childs[childs.length - 2]
                if (!lastNode.hasChildNodes()) {
                    lastNode = childs[childs.length - 3]
                }
                let lastIcon = lastNode.childNodes[0].childNodes[1]
                let first = childs[0].childNodes[0].childNodes[1]
                if (!updateFlag && lastIcon.childNodes.length > 1 && first.childNodes.length > 1) {
                    return
                }
                if (updateFlag) updateFlag = false
                QuerySubmissionUpdate(questiontag, lang, statusQus)
                pbSubmissionInfo = JSON.parse(GM_getValue("pbSubmissionInfo", "{}").toString())
                let subLst = pbSubmissionInfo[key]
                // console.log("替换数据: ", subLst)
                if (subLst == undefined || subLst.length == 0) return
                for (let i = 0; i < childs.length; i++) {
                    let v = childs[i]
                    let icon = v.childNodes[0].childNodes[1].childNodes[0]
                    let pa = icon.parentNode
                    let copy1 = icon.cloneNode(true);
                    copy1.innerText = subLst[i]["runtime"]
                    let copy2 = icon.cloneNode(true);
                    copy2.innerText = subLst[i]["memory"]
                    let copy3 = icon.cloneNode(true);
                    copy3.innerText = subLst[i]["submissionComment"] == null ? "无备注" : subLst[i]["submissionComment"]["comment"]
                    if (pa.childNodes.length > 1) {
                        // console.log("replace", copy1, copy2)
                        pa.replaceChild(copy1, pa.childNodes[1])
                        pa.replaceChild(copy2, pa.childNodes[2])
                        pa.replaceChild(copy3, pa.childNodes[3])
                    } else {
                        pa.appendChild(copy1);
                        pa.appendChild(copy2);
                        pa.appendChild(copy3);
                    }
                }
            }
        } catch (error) {
            // do nothing
        }
    }


    let now = getCurrentDate(1)
    preDate = GM_getValue("preDate", "")
    if (t2rate["tagVersion5"] == undefined || (preDate == "" || preDate != now)) {
        // 每天重置为空
        pbSubmissionInfo = JSON.parse("{}")
        GM_setValue("pbSubmissionInfo", JSON.stringify(pbSubmissionInfo))

        GM_xmlhttpRequest({
            method: "get",
            url: rakingUrl + "?timeStamp=" + new Date().getTime(),
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
            onload: function (res) {
                if (res.status === 200) {
                    // 保留唯一标识
                    t2rate = {}
                    let dataStr = res.response
                    let json = eval(dataStr)
                    for (const element of json) {
                        t2rate[element.ID] = element
                        t2rate[element.ID]["Rating"] = Number.parseInt(Number.parseFloat(element["Rating"]) + 0.5)
                    }
                    t2rate["tagVersion5"] = {}
                    console.log("everyday getdate once...")
                    preDate = now
                    GM_setValue("preDate", preDate)
                    GM_setValue("t2ratedb", JSON.stringify(t2rate))
                    t2rate = JSON.parse(GM_getValue("t2ratedb", "{}").toString())
                    preDate = GM_getValue("preDate", "")
                }
            },
            onerror: function (err) {
                console.log('error')
                console.log(err)
            }
        });
    }


    function clearAndStart(url, timeout, isAddEvent) {
        let start = ""
        let targetIdx = -1
        let pageLst = ['all', 'tag', 'pb', 'company', 'pblist', 'search']
        let urlLst = [allUrl, tagUrl, pbUrl, companyUrl, pblistUrl, searchUrl]
        let funcLst = [getData, getTagData, getpb, getCompanyData, getPblistData, getSearch]
        for (let index = 0; index < urlLst.length; index++) {
            const element = urlLst[index];
            if (url.match(element)) {
                targetIdx = index
                // console.log(targetIdx, url)
            } else if (!url.match(element)) {
                let tmp = GM_getValue(pageLst[index], -1)
                clearInterval(tmp)
            }
        }
        if (targetIdx != -1) start = pageLst[targetIdx]
        if (start != "") {
            id = setInterval(funcLst[targetIdx], timeout)
            GM_setValue(start, id)
        }
        if (isAddEvent) {
            window.addEventListener("urlchange", () => {
                let newUrl = window.location.href
                clearAndStart(newUrl, 1, false)
            })
        }
    }

    // 定时启动
    clearAndStart(window.location.href, 1, true)
    if (window.location.href.startsWith(allUrl)) {
        // 版本更新机制
        GM_xmlhttpRequest({
            method: "get",
            url: versionUrl + "?timeStamp=" + new Date().getTime(),
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
            onload: function (res) {
                if (res.status === 200) {
                    console.log("enter home page check version once...")
                    let dataStr = res.response
                    let json = JSON.parse(dataStr)
                    let v = json["version"]
                    let upcontent = json["content"]
                    if (v != version) {
                        layer.open({
                            content: '<pre style="color:#000">更新通知: <br/>leetcodeRating难度分插件有新的版本啦,请前往更新~ <br/>' + "更新内容: <br/>" + upcontent + "</pre>",
                            yes: function (index, layer0) {
                                let c = window.open(sciptUrl + "?timeStamp=" + new Date().getTime())
                                c.close()
                                layer.close(index)
                            }
                        });
                    } else {
                        console.log("leetcodeRating难度分插件当前已经是最新版本~")
                    }
                }
            },
            onerror: function (err) {
                console.log('error')
                console.log(err)
            }
        });

        // 获取茶数据
        GM_xmlhttpRequest({
            method: "get",
            url: teaUrl + "?timeStamp=" + new Date().getTime(),
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
            onload: function (res) {
                if (res.status === 200) {
                    console.log("enter home page gettea once...")
                    latestpb = {}
                    let dataStr = res.response
                    let json = JSON.parse(dataStr)
                    let al = json["算法趣题"][1]
                    latestpb["date"] = al[0] || { 'str': '' }; latestpb["pb"] = al[1] || { 'str': '' }; latestpb["url"] = al[1] || { 'url': '' };
                    latestpb["out"] = al[2] || { 'str': '' }; latestpb["nd"] = al[3] || { 'str': '' }; latestpb["solve"] = al[4] || { 'str': '' };
                    latestpb["blank"] = al[5] || { 'str': '' };
                    GM_setValue("latestpb", JSON.stringify(latestpb))
                    latestpb = JSON.parse(GM_getValue("latestpb", "{}").toString())
                }
            },
            onerror: function (err) {
                console.log('error')
                console.log(err)
            }
        });
    } else if (window.location.href.startsWith(pbUrl)) {
        // do nothing
        addListener()
    }

    // spig js 纸片人相关
    if (GM_getValue("switchperson")) {
        // url数据
        let imgUrl = "https://i.ibb.co/89XdTMf/Spig.png"
        //    let imgUrl = "https://raw.githubusercontents.com/zhang-wangz/LeetCodeRating/main/assets/samplespig.png"
        let checkUrl = "https://leetcode.cn/submissions/detail/.*/check/"

        const isindex = true
        const visitor = "主人"
        let msgs = []

        // 求等级用的数据
        let userTag = null
        let level = 0
        let score = 0
        const queryProcess = '\n    query userQuestionProgress($userSlug: String!) {\n  userProfileUserQuestionProgress(userSlug: $userSlug) {\n    numAcceptedQuestions {\n      difficulty\n      count\n    }\n    numFailedQuestions {\n      difficulty\n      count\n    }\n    numUntouchedQuestions {\n      difficulty\n      count\n    }\n  }\n}\n    '
        const queryUser = '\n    query globalData {\n  userStatus {\n    isSignedIn\n    isPremium\n    username\n    realName\n    avatar\n    userSlug\n    isAdmin\n    checkedInToday\n    useTranslation\n    premiumExpiredAt\n    isTranslator\n    isSuperuser\n    isPhoneVerified\n    isVerified\n  }\n  jobsMyCompany {\n    nameSlug\n  }\n  commonNojPermissionTypes\n}\n    '
        GM_addStyle(`
        .spig {
            display:block;
            width:154px;
            height:190px;
            position:absolute;
            top: -150px;
            left: 160px;
            z-index:9999;
        }
        #message {
            line-height:170%;
            color :#191919;
            border: 1px solid #c4c4c4;
            background:#ddd;
            -moz-border-radius:5px;
            -webkit-border-radius:5px;
            border-radius:5px;
            min-height:1em;
            padding:5px;
            top:-30px;
            position:absolute;
            text-align:center;
            width:auto !important;
            z-index:10000;
            -moz-box-shadow:0 0 15px #eeeeee;
            -webkit-box-shadow:0 0 15px #eeeeee;
            border-color:#eeeeee;
            box-shadow:0 0 15px #eeeeee;
            outline:none;
            opacity: 0.75 !important;
        }
        .mumu {
            width:154px;
            height:190px;
            cursor: move;
            background:url(${imgUrl}) no-repeat;
        }

        #level {
            text-align:center;
            z-index:9999;
            color :#191919;
        }
    `)

        const spig = `<div id="spig" class="spig" hidden>
                            <div id="message">正在加载中……</div>
                            <div style="height=80px"/>
                            <div id="mumu" class="mumu"></div>
                            <div id="level">level loading...</div>
                        </div>`
        const hitokoto = `<span class="hitokoto" id="hitokoto" style="display:none">Loading...</span>`
        $("body").append(spig, hitokoto)

        // 消息函数
        let showMessage = (a, b) => {
            if (b == null) b = 10000;
            $("#mumu").css({ "opacity": "0.5 !important" })
            $("#message").hide().stop();
            $("#message").html(a);
            $("#message").fadeIn();
            $("#message").fadeTo("1", 1);
            $("#message").fadeOut(b);
            $("#mumu").css({ "opacity": "1 !important" })
        };

        // 右键菜单
        jQuery(document).ready(function ($) {
            $("#spig").mousedown(function (e) {
                if (e.which == 3) {
                    showMessage(`秘密通道:<br/> <a href="${allUrl}" title="题库">题库</a>`, 10000);
                }
            });
            $("#spig").bind("contextmenu", function (e) {
                return false;
            });
        });

        function getscore(userTag) {
            let list = { "query": queryProcess, "variables": { "userSlug": userTag } };
            $.ajax({
                type: "POST", url: lcgraphql, data: JSON.stringify(list), success: function (res) {
                    let levelData = res.data.userProfileUserQuestionProgress.numAcceptedQuestions
                    levelData.forEach(e => {
                        if (e.difficulty == "EASY") score += e.count * 10
                        else if (e.difficulty == "MEDIUM") score += e.count * 20
                        else if (e.difficulty == "HARD") score += e.count * 100
                    });
                    level = score / 1000
                    $("#level").text("level: " + Math.round(level).toString())
                    console.log("目前纸片人的等级是: " + Math.round(level).toString())
                }, async: false, xhrFields: { withCredentials: true }, contentType: "application/json;charset=UTF-8"
            })
        }

        $.ajax({
            type: "POST", url: lcgraphql, data: JSON.stringify({ "query": queryUser, "variables": {} }), success: function (res) {
                userTag = res.data.userStatus.userSlug
                // console.log(userTag)
            }, async: false, xhrFields: { withCredentials: true }, contentType: "application/json;charset=UTF-8"
        })

        if (userTag != null) {
            getscore(userTag)
        } else {
            // console.log(userTag)
            $("#level").text("请登录后再尝试获取level")
        }
        // 监听分数提交
        let addListener2 = () => {
            XMLHttpRequest.prototype.send = function (str) {
                const _onreadystatechange = this.onreadystatechange;
                this.onreadystatechange = (...args) => {
                    if (this.readyState == this.DONE && this.responseURL.match(checkUrl)) {
                        let resp = JSON.parse(this.response)
                        // console.log(resp)
                        if (resp && resp.status_msg && resp.status_msg.includes("Accepted")) {
                            showMessage("恭喜主人成功提交， 当前分数为: " + score + ", 当前等级为: " + Math.round(level).toString())
                            console.log("恭喜主人成功提交， 当前分数为: " + score + ", 当前等级为: " + Math.round(level).toString())
                        } else if (resp && resp.status_msg && !resp.status_msg.includes("Accepted")) {
                            showMessage("很遗憾，主人提交失败，不过也不要气馁呀，加油! <br/> 当前分数为: " + score + ", 当前等级为: " + Math.round(level).toString())
                            console.log("很遗憾，主人提交失败，不过也不要气馁呀，加油! 当前分数为: " + score + ", 当前等级为: " + Math.round(level).toString())
                        }
                    }
                    if (_onreadystatechange) {
                        _onreadystatechange.apply(this, args);
                    }
                }
                return dummySend.call(this, str);
            }
        }
        addListener2()

        // 鼠标在消息上时
        jQuery(document).ready(function ($) {
            $("#message").hover(function () {
                $("#message").fadeTo("100", 1);
            });
        });

        // 鼠标在上方时
        jQuery(document).ready(function ($) {
            $(".mumu").mouseover(function () {
                $(".mumu").fadeTo("300", 0.3);
                msgs = ["我隐身了，你看不到我", "我会隐身哦！嘿嘿！", "别动手动脚的，把手拿开！", "把手拿开我才出来！"];
                let i = Math.floor(Math.random() * msgs.length);
                showMessage(msgs[i]);
            });
            $(".mumu").mouseout(function () {
                $(".mumu").fadeTo("300", 1)
            });
        });

        function msgPageWelcome(url, isAddEvent) {
            let urlLst = [allUrl, tagUrl, pbUrl, companyUrl, pblistUrl, searchUrl]
            let msgShow = ["欢迎来到题库页, 美好的一天从做每日一题开始~", "欢迎来到分类题库页面，针对专题练习有利于进步哦～", "欢迎来到做题页面，让我看看是谁光看不做？🐰", "欢迎来到公司题库，针对专门的公司题目练习有利于面试呢", "欢迎来到题单页面~", "欢迎来到搜索页，在这里你能搜到一切你想做的题！"]
            for (let index = 0; index < urlLst.length; index++) {
                const element = urlLst[index];
                if (url.match(element)) {
                    // console.log(msgShow[index])
                    showMessage(msgShow[index])
                }
            }
            if (isAddEvent) {
                window.addEventListener("urlchange", () => {
                    let newUrl = window.location.href
                    msgPageWelcome(newUrl, false)
                })
            }
        }

        // 开始
        jQuery(document).ready(function ($) {
            if (isindex) { // 如果是主页
                let now = (new Date()).getHours();
                if (now > 0 && now <= 6) {
                    showMessage(visitor + ' 你是夜猫子呀？还不睡觉，明天起的来么你？', 6000);
                } else if (now > 6 && now <= 11) {
                    showMessage(visitor + ' 早上好，早起的鸟儿有虫吃噢！早起的虫儿被鸟吃，你是鸟儿还是虫儿？嘻嘻！', 6000);
                } else if (now > 11 && now <= 14) {
                    showMessage(visitor + ' 中午了，吃饭了么？不要饿着了，饿死了谁来挺我呀！', 6000);
                } else if (now > 14 && now <= 18) {
                    showMessage(visitor + ' 中午的时光真难熬！还好有你在！', 6000);
                } else {
                    showMessage(visitor + ' 快来逗我玩吧！', 6000);
                }
                msgPageWelcome(window.location.href, true)
            }
            else {
                showMessage('力扣欢迎你～', 6000);
            }
            let top = $("#spig").offset().top + 150
            let left = document.body.offsetWidth - 160
            $("#spig").attr("hidden", false)
            $("#spig").css({ top: top, left: left })

            // $("#spig").animate({
            //     opacity: 1
            // },
            // {
            //     queue: false,
            //     duration: 1000
            // });
        });

        // 随时间自动漂浮，暂时不开启
        // jQuery(document).ready(function($) {
        //     window.setInterval(function() {
        //         msgs = [$("#hitokoto").text()];
        //         //if(weather.state) msgs.concat(weather.c);
        //         var i = Math.floor(Math.random() * msgs.length);
        //         var s = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.75, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.75];
        //         var i1 = Math.floor(Math.random() * s.length);
        //         var i2 = Math.floor(Math.random() * s.length);
        //         $(".spig").animate({
        //             left: document.body.offsetWidth / 2 * (1 + s[i1]),
        //             top: document.body.offsetheight / 2 * (1 + s[i2])
        //         },
        //         {
        //             duration: 2000,
        //             complete: showMessage(msgs[i])
        //         });
        //     },
        //     45000);
        // });


        // 随滚动条移动
        jQuery(document).ready(function ($) {
            let f = $(".spig").offset().top;
            $(window).scroll(function () {
                $(".spig").animate({
                    top: $(window).scrollTop() + f + 150
                },
                    {
                        queue: false,
                        duration: 1000
                    });
            });
        });

        // 鼠标点击时
        jQuery(document).ready(function ($) {
            let stat_click = 0;
            let i = 0;
            $(".mumu").click(function () {
                if (!ismove) {
                    stat_click++;
                    if (stat_click > 4) {
                        msgs = ["你有完没完呀？", "你已经摸我" + stat_click + "次了", "非礼呀！救命！OH，My ladygaga"];
                        i = Math.floor(Math.random() * msgs.length);
                        showMessage(msgs[i]);
                    } else {
                        msgs = ["筋斗云！~我飞！", "我跑呀跑呀跑！~~", "别摸我，有什么好摸的！", "惹不起你，我还躲不起你么？", "不要摸我了，我会告诉你老婆来打你的！", "干嘛动我呀！小心我咬你！"];
                        i = Math.floor(Math.random() * msgs.length);
                        showMessage(msgs[i]);
                    }
                    let s = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.75, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.75];
                    let i1 = Math.floor(Math.random() * s.length);
                    let i2 = Math.floor(Math.random() * s.length);
                    $(".spig").animate({
                        left: document.body.offsetWidth / 2 * (1 + s[i1]),
                        top: document.body.offsetHeight / 2 * (1 + s[i2])
                    },
                        {
                            duration: 500,
                            complete: showMessage(msgs[i])
                        });
                } else {
                    ismove = false;
                }
            });
        });

        // 拖动
        let _move = false;
        let ismove = false; // 移动标记
        let _x, _y; // 鼠标离控件左上角的相对位置

        jQuery(document).ready(function ($) {
            $("#spig").mousedown(function (e) {
                _move = true;
                _x = e.pageX - parseInt($("#spig").css("left"));
                _y = e.pageY - parseInt($("#spig").css("top"));
            });
            $(document).mousemove(function (e) {
                if (_move) {
                    let x = e.pageX - _x;
                    let y = e.pageY - _y;
                    let wx = $(window).width() - $('#spig').width();
                    let dy = $(document).height() - $('#spig').height();
                    if (x >= 0 && x <= wx && y > 0 && y <= dy) {
                        $("#spig").css({
                            top: y,
                            left: x
                        }); //控件新位置
                        ismove = true;
                    }
                }
            }).mouseup(function () {
                _move = false;
            });
        });

        // 纸片人一言api
        // $("#spig").attr("hidden", false)
        let hitokotohtml = function () {
            let msgShow = [$("#hitokoto").text()];
            showMessage(msgShow[0]);
            setTimeout(hitokotohtml, 15000)
        }
        setTimeout(hitokotohtml, 6000)

        function getkoto() {
            $.get("https://api.uixsj.cn/hitokoto/get?type=fart&code=json").then(res => { echokoto(res); }).catch(xhr => xhr)
            setTimeout(getkoto, 6000)
        }
        function echokoto(result) {
            let hc = eval(result);
            document.getElementById("hitokoto").textContent = hc.content;
            // console.log(hc.content)
        }
        setTimeout(getkoto, 5000);
    }

})();
