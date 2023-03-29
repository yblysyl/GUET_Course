package com.example.a2_3news;

import android.provider.BaseColumns;

public class NewsContract {
    private NewsContract(){}
    //实现BaseColumns接口以后，内部类就可以继承一个主键字段_ID，这也是很多android里的类所需要的，
    // 这虽然不是必须，但是可以使数据库和android的框架协调工作。
    //BaseColumns接口有两个常量：1.总行数_count   2.每行的独特的_ID
    public static class NewsEntry implements BaseColumns{
        public static final String TABLE_NAME="tbl_news";
        public static final String COLUMN_NAME_TITLE = "title";
        public static final String COLUMN_NAME_AUTHOR = "author";
        public static final String COLUMN_NAME_IMAGE = "image";

    }

}
