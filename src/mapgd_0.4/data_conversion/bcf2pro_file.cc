#include "bcf2pro_file.h"

void Bcf2pro_file::read_text(Locus &data)
{
	if (profile_) read_text_profile(data);
	else {
		//TODO Check for table_open instead?
		std::string scaffold;
		id1_t pos;
		*in_ >> scaffold;
		*in_ >> pos;
		if (!in_->good() ) {
//			std::cerr << *in_.
//			*in_ >> scaffold;
//			*in_ >> pos;
//			std::cerr << "shit!\n";
			this->close();
		} else {
//			std::cerr << "cool!\n";
			data.set_abs_pos(file_index_.get_abs_pos(scaffold, pos) );
			mpileup(*in_, data, offset_, columns_);
			if (in_->eof() ) this->close();
		}
	}
}

Locus Bcf2pro_file::read_header(void){
	if (profile_) return  read_header_profile();
	else {
		buffer_.buffer_on();
		buffer_.reread_off();
		std::string line;
		std::vector <std::string> columns;
		std::getline(*in_, line);
//		std::cerr << line << std::endl;
		columns=split(line, '\t');
		Locus data( (columns.size()-offset_)/columns_ );	//TODO FIX IMEDIATELY!! (TOMORROW).

/*		in_->putback('\n');
		for(std::string::iterator c=line.end(); (c--)!=line.begin();) {
			in_->putback(*c);
		}*/
		buffer_.buffer_off();
		buffer_.reread_on();

		table_open_=true;
		return data;
	} 
}

void
Bcf2pro_file::set_mpileup(const int &offset, const int &columns)
{
	columns_=columns;
	offset_=offset;
}
