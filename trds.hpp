

//1
template <typename T>
class File {
public:
  virtual bool estVide() const =0;
  virtual const T &premier() const=0;
  virtual void defiler() =0;
  virtual void enfiler(const T &elt) =0;
  virtual const std::string toString() const=0;
  friend std::ostream& operator<<(std::ostream &f,const File<T>& file){
    return f<<fi.toString();
  }
};



//2
class FileVideException : public std::exception {
public:
  virtual const char* what() const noexcept override{
    return "File Vide Exception";
  }
};



//3

template <typename T>
class FileVecteur : public File<T> {
protected:
  std::vector<T> LesElements;

public:
  virtual bool estVide() const override{
    return this->LesElements.empty();
  }
  virtual const T &premier() const override{
    if (this->estVide()) {
      throw FileVideException();
    }
    return this->LesElements.front();
  }
  virtual void defiler override{
    if (this->estVide()){
      throw FileVideException();
    }
    return this->LesElements.erase(LesElements.begin());
  }
  virtual void enfiler(const T &elt) override{
    return this->LesElements.push_back(elt);
  }
  virtual const std::string toString() const override{
    std::ostringstream oss;
    oss << "["
     if (!this->estVide()){
       oss << this->LesElements[0] << " / ";
       for (unsigned int i=1, i<this->LesElements.size(), i++){
	 oss << this->LesElements[i] << " / "
	   }
     }
    oss << "]" ;
    return oss.str();
     
    }
};
    
//4

class Vehicule {
protected:
  int classe;

public:
  //constructeur
  Vehicule(const int c) : classe(c){
    assert(c>=1 && c<5);
  }
  
  int getClasse() const{
    return this->classe;
  }
};
  
//5

class Cabriolet : public Vehicule {
public:
  Cabriolet() : Vehicule(1);
};


class Moto : public Vehicule {
public:
  Moto() : Vehicule(5);
};			   

//6

class Peage {
private:
  double tarifs[6]={0,7,9,10,15,3};
public:
  double getTarif(const Vehicule *V) const{
    return this->tarifs[V->getClasse()];
  }
  double encaisser(File<Vehicule*> *p)const{
    double somme=0.0;
    while(!p->estVide()){
      somme+= this->getTarif(f->premier());
      p->defiler();
    }
    return somme;
  }
};
  

int main() {
  File<Vehicule*> *fv = new FileVecteur<Vehicule*>();
  fv->enfiler(new Cabriolet());
  fv->enfiler(new Cabriolet());
  fv->enfiler(new Cabriolet());
  fv->enfiler(new Moto());
  fv->enfiler(new Moto());
  Peage p;
  std::cout << p.encaisser(fv) << std::endl;
  return EXIT_SUCCESS;
}
   
  
  
