typedef int Rank; //7*
#define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可设置为更大）
template <typename T> class Vector{ //向量模板类
protected:
    Rank _size;int _capacity;T* _elem;//规模、容量、数据区
    void copyFrom(T const* A,Rank lo,Rank hi);//复制数组区间A［10，hi）
    void expand();//空间不足时扩容
    void shrink();//装填因子过小时压缩
    bool bubble(Rank lo,Rank hi);//扫描交换
    void bubbleSort(Rank lo,Rank hi);//起泡排序算法
    Rank max(Rank lo,Rank hi);//选取最大元素
    void selectionSort(Rank lo,Rank hi);//选择排序算法
    void merge ( Rank lo, Rank mi, Rank hi ); //EHiZ
    void mergeSort(Rank lo,Rank hi);//归并排序算法
    Rank partition(Rank lo,Rank hi);//轴点构造算法
    void quickSort(Rank lo,Rank hi);//快速排序算法
    void heapSort (Rank lo,Rank hi);//堆排序
public:
    Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)
    {_elem=new T[_capacity=c];for (_size=0;_size<s;_elem[_size++]=v);}
    Vector (T const* A,Rank n){ copyFrom(A,0,n);}/数组整体复制
    Vector ( T const* A, Rank lo, Rank hi) { copyFrom ( A, lo, hi); } //Xi
    Vector ( Vector<T>const& V){copyFrom (V._elem, 0, V._size );} //向量整体复制
    Vector ( Vector<T>const& V, Rank lo, Rank hi) { copyFrom (V. _elem, lo, hi); } //Xi#
    //析构函数
    ~Vector () {delete []_elem;}//释放内部空间
    // 只读访问接口
    Rank size()  const { return_size;}//规模
    bool empty() const { return !_size; } 
    int disordered()const;//判断向量是否已排序
    Rank find (T const&e)const {return find(e, 0,_size);}//无序向𢶤整体查找
    Rank find(T const& e,Rank lo,Rank hi) const;//无序向量区间查找
    Rank search(T const& e )const//有序向量整体查找
    { return (0 >= size ) ? -1 : search (e, o, _size ); }
    Rank search(T const& e, Rank lo,Rank hi)const;//有序向量区间查找
    // 可写访问接口
    T& operator[](Rank r)const;//重载下标操作符，可以类似于数组形式引用各元素
    Vector<T> & operator=(Vecton<T> const&);//重载赋值操作符，以便直接克隆向量
    T remove(Rank r);//删除秩为r的元素
    int remove(Rank lo,Rank hi);//删除秩在区间［10hi）之内的元素
    Rank insert(Rank r,T const& e);//插入元素
    Rank insert (T const& e) { return insert (_size,e);}//默认作为末元素插入
    void sort(Rank lo,Rank hi);//双［10,hi）排序
    void sort() { sort (0,_size);}//整体排序
    void unsort (Rank lo, Rank hi); //XI[lo, hi)Ffl
    void unsort(){ unsort (0,_size);}//整体置乱
    int deduplicate();//无序去重
    int uniquify();
    //有序去重
// 遍历
    void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部性修改）
    template <typename VST>void traverse(VST&);
};