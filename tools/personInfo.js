(function() {
    var that = {};
    document.body.appendChild((function() {
        var element = document.createElement("script");
        element.src = 'https://static.leetcode-cn.com/cn-legacy-assets/jquery/dist/jquery.min.js?v=3.3.1';
        return element;
    })());
    that.siteRank = $(".mb-6 .ttext-label-1").text();
    that.passPreoblem = $('.mr-8.mt-6 .text-label-1').text();
    that.contestScore = $('.my-4 .mr-4 .text-label-1').first().text();

    function add(p, i, a, b) {
        p = $(p[i]).text().split('/')
        that[a] = p[0];
        that[b] = p[1];
    }

    add($('.my-4 .mr-4 .text-label-1'), 1, "globalRank", "globalNum");
    add($('.my-4 .mr-4 .text-label-1'), 2, "countryRank", "countryNum");
    add($('.mx-3 .space-y-2 .items-center'), 0, "sampleRank", "sampleNum");
    add($('.mx-3 .space-y-2 .items-center'), 1, "mediumRank", "mediumNum");
    add($('.mx-3 .space-y-2 .items-center'), 2, "hardRank", "hardNum");

    var output = [];
    output.push(that.siteRank); // 全站排名
    output.push(that.passPreoblem); // 通过题目
    output.push(' '); // 日增题目
    output.push(' '); // 日增排名
    output.push(' '); // 当天一题增加排名
    output.push(' '); // 累计一题增加排名
    output.push(that.contestScore); // 竞赛积分
    output.push(that.countryRank); // 全国排名
    output.push(that.countryNum); // 全国人数
    output.push(' '); // 全国占比
    output.push(that.globalRank); // 全球排名
    output.push(that.globalNum); // 全球人数
    output.push(' '); // 全球占比
    output.push(that.sampleRank); // 通过简单
    output.push(that.sampleNum); // 简单
    output.push(' '); // 简单比例
    output.push(that.mediumRank); // 通过中等
    output.push(that.mediumNum); // 中等
    output.push(' '); // 中等比例
    output.push(that.hardRank); // 通过困难
    output.push(that.hardNum); // 困难
    output.push(' '); // 困难比例


    console.log(output.join("\t"));
})();