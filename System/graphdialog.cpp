#include "graphdialog.h"
#include "ui_graphdialog.h"

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog)
{
    ui->setupUi(this);

//    QVBoxLayout *vbox = new QVBoxLayout(this);
//    vbox->setAlignment(Qt::AlignBaseline);
//    vbox->insertWidget(2,ui->label/*,Qt::AlignHCenter*/);
//    vbox->insertWidget(4,ui->comboBox);
//    vbox->insertWidget(6,ui->label_2);
//    vbox->insertWidget(8,MSCB);
//    vbox->insertWidget(10,ui->buttonBox);
//    setLayout(vbox);

    for(int i=0;i<16;i++) ui->MSCB->addItem(Country::NAME[i]);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(build()));
}

GraphDialog::~GraphDialog()
{
    delete ui;
}

void GraphDialog::build(){
    qDebug()<<"ShowGraph";

    QFont font;
    font.setFamily("HarmonyOS Sans");

    QStringList list=ui->MSCB->CheckText();
    QChart *chart = new QChart();
    QBarSeries *cset=new QBarSeries();
    int col=ui->comboBox->currentIndex();

    int MAXY=0;

    for(auto it=list.begin();it!=list.end();it++){
        qDebug()<<*it;
        QBarSet *data=new QBarSet(*it);

        Country *st=new Country;
        st->read(*it);

        for(int i=1;i<=6;i++){
            int res=st->calc_month(i,col);
            *data<<res;
            MAXY=max(MAXY,res);
        }

        data->setLabelColor(Qt::black);
        data->setLabelFont(font);

        cset->append(data);
    }



//    QBarSet *set0 = new QBarSet("Mhx");
//    QBarSet *set1 = new QBarSet("Feb");
//    QBarSet *set2 = new QBarSet("Mar");
//    QBarSet *set3 = new QBarSet("Apr");
//    QBarSet *set4 = new QBarSet("May");
//    QBarSet *set5 = new QBarSet("Jun");

//    *set0 << 1 << 2 << 3 << 4 << 5 << 6;// Jane 6个月份的值
//    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
//    *set2 << 3 << 5 << 8 << 19<< 8 << 5;
//    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
//    *set4 << 9 << 7 << 5 << 3 << 1 << 2;
//![1]

//![2]
//    QBarSeries *series = new QBarSeries();
//    series->append(set0);
//    series->append(set1);
//    series->append(set2);
//    series->append(set3);
//    series->append(set4);

//![2]

//![3]
    cset->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    cset->setLabelsVisible(true);

    chart->addSeries(cset);
    QString title="已选国家的"+ui->comboBox->currentText()+"数据";
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QValueAxis *yxis=new QValueAxis();

    axis->append(categories);
    yxis->setRange(0,ceil(MAXY*1.5/1000)*1000);

    chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
    chart->setAxisX(axis, cset);//设置坐标轴
    chart->setAxisY(yxis, cset);
//![4]

//![5]
    chart->legend()->setVisible(true); //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部
//![5]

//![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


//![6]

//![7]
    QMainWindow *window=new QMainWindow;
    window->setCentralWidget(chartView);
    window->setWindowTitle("柱状图可视化界面");
    window->setFont(font);
    window->resize(1600, 900);
    window->show();
}