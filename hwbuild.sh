echo "Writing build_type..."

echo "#ifndef BUILD_TYPE_H
#define BUILD_TYPE_H

#define HARDWARE_BUILD

#endif" > core/build_type.h
echo "Writing makefile..."
echo "Renaming Makefile.old..."
mv Makefile Makefile.old1
mv Makefile.old Makefile
mv Makefile.old1 Makefile.old
echo "Done configuring environment for HARDWARE_BUILD"
