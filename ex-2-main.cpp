#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#define mcxi_max 9999
#define mcxi_min 0
#define mcxi_maximum_unit 1000

namespace cpp2 {
    /* --------------------------------------------------------------------- */
    /*
       mcxi

       mcxi 記法を解析するクラスです。
     */
    /* --------------------------------------------------------------------- */
    class mcxi {
    public:
        /* ----------------------------------------------------------------- */
        /*
           mcxi

           指定された文字列を解析して、オブジェクトを初期化します。
           以下の場合には例外が送出されます。

           1. [2-9,m,c,x,i] 以外の文字が出現した場合
           2. 2 文字続けて数字 (2-9) が出現した場合
           3. m, c, x, i がこの順序で出現しなかった場合
              ただし、例えば mx のように、特定の文字をスキップする事は許容
              されます。
         */
        /* ----------------------------------------------------------------- */
        mcxi(const std::string& s) : value_(0) {
        	int num = 0;
        	uint16_t mcxi_unit_order = mcxi_maximum_unit;

        	for(auto pos = s.begin(); pos != s.end(); pos++){
        		if(*pos <= '1'){
        			throw std::invalid_argument("invalid args, 1");
        		}
        		if(*pos >= '2' && *pos <= '9'){
        			//2
        			if(num != 0){
        				throw std::invalid_argument("invalid args, 2");
        			}
        			num = *pos - '0';
        		}
        		//1
        		else{
        			//1
        			if(unit(*pos) == -1){
        				throw std::invalid_argument("invalid args, 1");
        			}
        			//fsm in order of m -> c -> x -> i
        			if(mcxi_unit_order <= unit(*pos)){
        				throw std::invalid_argument("invalid args, 3");
        			}
        			int u = unit(*pos);

        			value_ += std::max(num,1) * u; //std::max
        			num = 0;
        		}
        	}
        }


        /* ----------------------------------------------------------------- */
        /*
           operator+

           2 つのオブジェクトの加算結果を取得します。
         */
        /* ----------------------------------------------------------------- */
        mcxi operator+(const mcxi& rhs) {
        	mcxi ret("");
        	ret.value_ = this->value_ + rhs.value_;
        	//error handle
        	if(ret.value_ > mcxi_max){
        		throw std::overflow_error("overflow occurred");
        	}
            return ret;
        }

        /* ----------------------------------------------------------------- */
        /*
           to_string

           現在の値を mcxi 記法に変換します。
         */
        /* ----------------------------------------------------------------- */
        std::string to_string() const {
        	if(value_ > mcxi_max || value_ < mcxi_min){
        		throw std::range_error("");
        	}

        	uint16_t temp;
        	std::stringstream ret;
        	//m
			temp = value_ / 1000;
			if (temp == 1){
				ret << 'm';
			}
			if (temp > 1){
				ret << temp;
				ret << 'm';
			}

			//x
			temp = (value_ /100) % 10;
			if (temp == 1){
				ret << 'c';
			}
			if (temp > 1){
				ret << temp;
				ret << 'c';
			}

			//c
			temp = (value_ / 10 ) % 10;
			if (temp == 1){
				ret << 'x';
			}
			if (temp > 1){
				ret << temp;
				ret << 'x';
			}

			//i
			temp = value_ % 10;
			if (temp == 1){
				ret << 'i';
			}
			if (temp > 1){
				ret << temp;
				ret << 'i';
			}
			return ret.str();
        }

    private:
        int unit(char c){
        	switch(c){
				case 'm' : return 1000;
				case 'c' : return 100;
				case 'x' : return 10;
				case 'i' : return 1;
				default : return -1;
        	}
        }

        int value_;
    };
}
 
int main(){
	try{
		cpp2::mcxi a0("xi");
		cpp2::mcxi b0("x9i");

		std::cout << a0.to_string() << std::endl;;

		cpp2::mcxi result0 = a0 + b0;
		std::cout << "3x" <<" " << result0.to_string() << std::endl;

		cpp2::mcxi a1("i");
		cpp2::mcxi b1("9i");
		cpp2::mcxi result1 = a1 + b1;
		std::cout << "x" << " " << result1.to_string() << std::endl;

		cpp2::mcxi a2("c2x2i");
		cpp2::mcxi b2("4c8x8i");
		cpp2::mcxi result2 = a2 + b2;
		std::cout << "6cx" << " " << result2.to_string() << std::endl;

		cpp2::mcxi a3("m2ci");
		cpp2::mcxi b3("4m7c9x8i");
		cpp2::mcxi result3 = a3 + b3;
		std::cout << "5m9c9x9i" << " " << result3.to_string() << std::endl;

		cpp2::mcxi a4("9c9x9i");
		cpp2::mcxi b4("i");
		cpp2::mcxi result4 = a4 + b4;
		std::cout << "m" << " " << result4.to_string() << std::endl;

		cpp2::mcxi a5("i");
		cpp2::mcxi b5("9m9c9x8i");
		cpp2::mcxi result5 = a5 + b5;
		std::cout << "9m9c9x9i" << " " << result5.to_string() << std::endl;

		cpp2::mcxi a6("m");
		cpp2::mcxi b6("i");
		cpp2::mcxi result6 = a6 + b6;
		std::cout << "mi" << " " << result6.to_string() << std::endl;

		cpp2::mcxi a7("i");
		cpp2::mcxi b7("m");
		cpp2::mcxi result7 = a7 + b7;
		std::cout << "mi" << " " << result7.to_string() << std::endl;

		cpp2::mcxi a8("m9i");
		cpp2::mcxi b8("i");
		cpp2::mcxi result8 = a8 + b8;
		std::cout << "mx" << " " << result8.to_string() << std::endl;

		cpp2::mcxi a9("9m8c7xi");
		cpp2::mcxi b9("c2x8i");
		cpp2::mcxi result9 = a9 + b9;
		std::cout << "9m9c9x9i" << " " << result9.to_string() << std::endl;
	}
	catch(...){
		std::cout << "some exception" << std::endl;
	}

    return 0;
}
