#include <boost/scoped_ptr.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/once.hpp>
#include <string>
#include <iostream>


class Parent {
    public:
    void open(){ std::cout<<"parent do open\n";} 
    Parent(){ std::cout << "construct Parent\n"; } 
    ~Parent () { std::cout << "~release Parent\n"; } 
};

struct Child {
    std::string _name;
    Parent * _pant;  
    void dosome(){ std::cout<<"do something"<<_name<<"\n";} 
    int doother (){ 
        _pant->open();     
        return 2;
    }
    Child(std::string name):_name(name) 
    {
        _pant = new Parent(); 
        std::cout << "construct Child\n"; 
    } 
    ~Child() { 
        std::cout << "~release Child\n"; 
        if(_pant){
            delete _pant; 
        }
    } 
};

class Factory
{
    public:
        static Factory *GetInstance();

        boost::shared_ptr<Child>
            getSharedFileLockBox( const std::string& lockBoxFileName);

        int deleteShareChild( const std::string& lockBoxFileName );

    private:
        static Factory *factory;
        static void _createInstance();
        static boost::once_flag _instance_once;
        Factory (){ std::cout << "Factory created\n"; };
        ~Factory (){ std::cout << "Factory release\n"; };

        boost::shared_ptr<Child>
            _getSharedChild();

        boost::recursive_mutex _mutex;
        int _deleteShareChild( const std::string & name);

        typedef std::map<const std::string, boost::shared_ptr<Child> > SharedChildMapT;
        SharedChildMapT _sharedChild;

}; 

Factory * Factory::factory = NULL;
boost::once_flag Factory::_instance_once = BOOST_ONCE_INIT;

Factory * Factory::GetInstance(){
    boost::call_once(&_createInstance, _instance_once);
    return factory;
}

void Factory::_createInstance()
{
    factory  = new Factory();
}

boost::shared_ptr<Child> Factory::getSharedFileLockBox(const std::string & name)
{
    boost::lock_guard<boost::recursive_mutex> lock(_mutex);
    int a = 1;
    if(name == ""){
    return (boost::shared_ptr< Child > ()); 
    }
    SharedChildMapT::iterator it;
    it = _sharedChild.find(name);

    if( it == _sharedChild.end()){
    std::cout<<"new a child "<<name<<"\n";
     boost::shared_ptr<Child> newC = ( boost::shared_ptr<Child>) new Child(name);
     int x = newC->doother();
    if( x ==2){
        newC.reset();
       return newC; 
    }     
     _sharedChild[name] = newC; 
     return newC;
    }
    else
    {
    std::cout<<"find existing child "<<name<<"\n";
        boost::shared_ptr<Child > item = (*it).second; 
        return item;
    }
}

int Factory::deleteShareChild(const std::string & name)
{
    std::cout<<"deleteSharedFileLockBox "<<name<<"\n";
    return 0;
}

int Factory::_deleteShareChild(const std::string & name)
{
    std::cout<<"_deleteSharedFileLockBox "<<name<<"\n";
    return 0;
}

class MyClass {
    boost::scoped_ptr<int> ptr;
    public:
    MyClass() : ptr(new int) { *ptr = 0; }
    int add_one() { return ++*ptr; }
};


void testSome()
{
    int error = 0;
    Factory * fat = Factory::GetInstance();
    boost::shared_ptr<Child> cld = fat->getSharedFileLockBox("test");
    if(!cld){
      cld = fat->getSharedFileLockBox("test");
      if(!cld){
        error = 1; 
      } 
    }else{
    cld->dosome();
    }
    if(error){
      throw std::runtime_error("Lockbox error: " + error); 
    }
}

int main()
{
    /*
    boost::scoped_ptr<Shoe> x(new Shoe);
    MyClass my_instance;
    std::cout << my_instance.add_one() << '\n';
    std::cout << my_instance.add_one() << '\n';
    */
    int trynum = 0;
    while(trynum < 3){
        try{
            for( int i =0; i<3; i++)
            {
                testSome();
            }
            trynum = 3;
        }
        catch(const std::exception & e ){
            std::cout<<"catch exception" << e.what() <<"\n";
            trynum++;
        }
    }
    for( int j =0; j<9999999; j++);
}
