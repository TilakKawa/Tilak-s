/* Citation and Sources...
 * Final Project Milestone 5
 * Module: ReadWritable
 * Filename: ReadWritable.h
 * Version 1.0
 * Author	 Tilak Kawa 
 * Revision History
 * -----------------------------------------------------------
 *  Date        Reason
 *  2022/11/23  Preliminary release
 *  2022/11/23  Debugged DMA
 *  -----------------------------------------------------------
 *  I have done all the coding by myself and only copied the code 
 *  that my professor provided to complete my project milestones.
 *  -----------------------------------------------------------
 *  */


#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__

#include <iostream>

using namespace std;
namespace sdds {
	class ReadWritable {
		bool isCSMode;
	public:
		ReadWritable();
		virtual ~ReadWritable();
		virtual std::istream& read(std::istream&) = 0;
		virtual  std::ostream& write(std::ostream&) const = 0;
		bool isCsv() const;
		void setCsv(bool);
		friend std::istream& operator >> (std::istream&, ReadWritable&);
		friend std::ostream& operator << (std::ostream&, const ReadWritable&);


	};
}
#endif
