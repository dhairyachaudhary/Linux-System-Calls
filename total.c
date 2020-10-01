/*
	Name: Dhairya Chaudhary
	Roll No.: 2019035
*/

#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include<stdlib.h>
#include <math.h>

void tostring(char str[], int n){
	//Function to convert integer to string
	int p=n;
	int len=0;
	while (p != 0){
		len++;
		p=p/10;
	}

	int i, r;
	for (i=0; i<len; i++){
		r = n%10;
		n = n/10;
		str[len-(i+1)]=r+'0';
	}
	str[len]='\0';
}

void readattribute(int fd, char* thisChar, char* retval){
	//Reads from the file and returns the string till the next comma is encountered
	while (1){
		read(fd, thisChar, 1); 
		if (strcmp(thisChar,",")==0){
			//loop reads from file character by character till a comma is encountered
			break;
		}
		strcat(retval,thisChar);
	}
}

int main() {
	pid_t ret_value;
	//Spawns child process
	ret_value=fork();

	if (ret_value<0){
		//Error handling
		exit(1);
	} 

	else if (ret_value==0){
		//Inside child process
		//Opening file to be read from
		int fd;
		fd = open("file.csv", O_RDONLY); 
		if (fd < 0) { 
			//Error handling
			perror("r1"); exit(1); 
		} 

		char *thisChar = (char *) calloc(1, sizeof(char)); 
		char *header = (char *) calloc(1, sizeof(char)); 

		while (1){
			//We don't need the header, so this is just read and not used further
			read(fd,header,1);
			if (strcmp(header,"\n")==3){
				//The header ends at the first newline character
				break;
			} 
		}

		int fd1, fd2, sz,len=0,status=1; 

		//Opening the file to write to
		fd1 = open("sectionA.txt", O_RDWR); 
		if (fd1 < 0) { 
			//Error handling
			perror("r1"); exit(1); 
		} 

		fd2 = open("sectionA.txt", O_RDWR); 
		if (fd2 < 0) { 
			//Error handling
			perror("r1"); exit(1); 
		}

		while (status){
			//We'll store the student's attributes that we read in these
			char *studentID = (char *) calloc(1, sizeof(char)); 
			char *sec = (char *) calloc(1, sizeof(char)); 
			char *marks1 = (char *) calloc(1, sizeof(char)); 
			char *marks2 = (char *) calloc(1, sizeof(char)); 
			char *marks3 = (char *) calloc(1, sizeof(char)); 
			char *marks4 = (char *) calloc(1, sizeof(char));
			int m1,m2,m3,m4;

			readattribute(fd, thisChar,studentID);

			readattribute(fd,thisChar,sec);
			if (strcmp(sec,"B")==0){
				//As soon as we reach the section B part of the file, status will be set to 0 and we'll exit
				//Section B's computations will be done by parent process
				status=0;
			} else {
				//Writing Student IDs of section A students to the file
				write(fd1, studentID, strlen(studentID));
				write(fd1, " ", 1);
				len=len+strlen(studentID)+1;
			}

			//Reading the marks and converting them to integer so we can compute average
			readattribute(fd, thisChar,marks1);
			m1=atoi(marks1);
			readattribute(fd, thisChar,marks2);
			m2=atoi(marks2);
			readattribute(fd, thisChar,marks3);
			m3=atoi(marks3);

			while (1){
				//For the last entry of a row (marks in A4), we'll look for newline character and not comma
				read(fd, thisChar, 1); 
				if (strcmp(thisChar,"\n")==3){
					break;
				} 
				strcat(marks4,thisChar);
			}
			m4=atoi(marks4);

			//Calculating average and converting it to a string
			char avg[5];
			tostring(avg,((m1+m2+m3+m4)/4));

			if (status==0){
			} else {
				//We write average marks of section A students to the file
				write(fd1, avg, strlen(avg));
				write(fd1, "\n", 1);
				len=len+strlen(avg)+1;
			}		
		}

		//Writing file contents to stdout
		char buffer[len];
		write(1, buffer, read(fd2, buffer, len)); 

		//Closing all opened files
		if (close(fd)<0){
			//Error handling
			perror("c1"); 
			exit(1); 
		} if (close(fd1)<0){
			//Error handling
			perror("c1"); 
			exit(1); 
		} if (close(fd2)<0){
			//Error handling
			perror("c1"); 
			exit(1); 
		}

		//Exiting with status 0
		exit(0);
	} 

	else {
		waitpid(-1);
		//Used to make the parent process wait for the child

		//Inside child process
		//Opening file to be read from
		int fd3;
		fd3 = open("file.csv", O_RDONLY); 
		if (fd3 < 0) { 
			//Error handling
			perror("r1"); exit(1); 
		} 

		char *thisChar = (char *) calloc(1, sizeof(char)); 

		int fd4, fd5, sz,len2=0,status=1; 

		fd4 = open("sectionB.txt", O_RDWR); 
		if (fd4 < 0) { 
			//Error handling
			perror("r1"); exit(1); 
		} 

		fd5 = open("sectionB.txt", O_RDWR); 
		if (fd5 < 0) { 
			//Error handling
			perror("r1"); exit(1); 
		}

		while (status){
			//We'll store the student's attributes that we read in these
			char *studentID = (char *) calloc(1, sizeof(char)); 
			char *sec = (char *) calloc(1, sizeof(char)); 
			char *marks1 = (char *) calloc(1, sizeof(char)); 
			char *marks2 = (char *) calloc(1, sizeof(char)); 
			char *marks3 = (char *) calloc(1, sizeof(char)); 
			char *marks4 = (char *) calloc(1, sizeof(char));
			int m1,m2,m3,m4;

			readattribute(fd3, thisChar,studentID);

			readattribute(fd3,thisChar,sec);

			if (strcmp(sec,"B")==0){
				//We write the student IDs of students of section B to our file
				write(fd4, studentID, strlen(studentID));
				write(fd4, " ", 1);
				len2=len2+strlen(studentID)+1;
			}
			
			//Reading the marks and converting them to integer so we can compute average
			readattribute(fd3, thisChar,marks1);
			m1=atoi(marks1);
			readattribute(fd3, thisChar,marks2);
			m2=atoi(marks2);
			readattribute(fd3, thisChar,marks3);
			m3=atoi(marks3);

			while (1){
				sz = read(fd3, thisChar, 1); 
				if (sz==0){
					//Corner case, this means we have reached EOF
					status=0;
					break;
				}
				if (strcmp(thisChar,"\n")==3){
					//For the last entry of a row (marks in A4), we'll look for newline character and not comma
					break;
				} 
				strcat(marks4,thisChar);
			}
			m4=atoi(marks4);

			if (strcmp(sec,"B")==0){
				//We compute and write the average of students of section B to our file
				char avg[5];
				tostring(avg,((m1+m2+m3+m4)/4));

				write(fd4, avg, strlen(avg));
				write(fd4, "\n", 1);
				len2=len2+strlen(avg)+1;	
			}
		}

		//Writing file contents to stdout
		char buffer2[len2];
		write(1, buffer2, read(fd5, buffer2, len2)); 

		//Closing all opened files
		if (close(fd3)<0){
			//Error handling
			perror("c1"); 
			exit(1); 
		} if (close(fd4)<0){
			//Error handling
			perror("c1"); 
			exit(1); 
		} if (close(fd5)<0){
			//Error handling
			perror("c1"); 
			exit(1); 
		}
	} 
}