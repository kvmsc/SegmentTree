class SegmentTree{
    /*
    Input: Data Vector, Operator Function and Data-to-Node Value Transformer[OPTIONAL]
    Requires: std::vector, std::function, math.h
    Future Improvements: Create templates for using data types other than integers
    REFERENCES:
        https://stackoverflow.com/questions/8711391/should-i-copy-an-stdfunction-or-can-i-always-take-a-reference-to-it
        https://www.geeksforgeeks.org/lambda-expression-in-c/
        https://oopscenities.net/2012/02/24/c11-stdfunction-and-stdbind/
    NOTE:
        Identity is not required here since the recursive calls are already pruned
    */
    typedef function<int (int,int)> opFunc;
    typedef function<int (int)> nodeFunc;
    private:
        vector<int>& data;
        vector<int> tree;
        opFunc operand;
        nodeFunc dataToNode;
        int size;
        int treesize;
        
        int left(int pos){
            return (2*pos+1);
        }
        
        int right(int pos){
            return (2*pos+2);
        }

        int mid(int left,int right){
            return left + (right-left)/2;
        }
        
        void _build(int start,int end,int pos){
            if(start == end){
                tree[pos] = dataToNode(data[start]);
                return;
            }
            _build(start,mid(start,end),left(pos));
            _build(mid(start,end)+1,end,right(pos));
            tree[pos] = operand(tree[left(pos)],tree[right(pos)]);
        }

        void _update(int idx,int start,int end,int pos){
            if(start==end){
                tree[pos] = dataToNode(data[idx]);
                return;
            }
            if(idx<=mid(start,end))
                _update(idx,start,mid(start,end),left(pos));
            else
                _update(idx,mid(start,end)+1,end,right(pos));
            tree[pos] = operand(tree[left(pos)],tree[right(pos)]);
        }

        int _query(int qstart,int qend,int start,int end,int pos){
            if(qstart==start && qend==end)
                return tree[pos];
            int middle = mid(start,end);
            
            if(qstart>middle)
                return _query(qstart,qend,middle+1,end,right(pos));
            if(qend<=middle)
                return _query(qstart,qend,start,middle,left(pos));
            return operand(_query(qstart,middle,start,middle,left(pos)),_query(middle+1,qend,middle+1,end,right(pos)));
        }
    public:
        SegmentTree(vector<int>& _data, opFunc _op, nodeFunc _dToNode = [=](int val){return val;}) 
        : data(_data)
        , operand(_op)
        , dataToNode(_dToNode)
        {
            size = data.size();
            treesize = pow(2,int(log2(size))+2);
            tree.assign(treesize,0);
            _build(0,size-1,0);
        }
        void update(int idx,int val){
            data[idx] = val;
            _update(idx,0,size-1,0);
        }
        
        int query(int start,int end){
            return _query(start,end,0,size-1,0);
        }

};
