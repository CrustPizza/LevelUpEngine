"""
*********************************
*								*
*	LUE Exporter.py				*
*								*
*	Created : 2022/07/05		*
*	Updated : 2022/07/05		*
*********************************
"""

# Blender Script를 작성하기 위해 필요한 API Import
import bpy

# time은 Standard Library인 듯
import time

# 특정 클래스나 함수를 통째로 가져오고 싶을 때
# from / import를 하는 것 같다.
# 이걸 안한다면 StringProperty를 사용할 때
# bpy.props.StringProperty()로 사용해야 되나?
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, FloatProperty

class ExportLUE( bpy.types.Operator, ExportHelper ):

	# 식별자로서의 역할만 하는 것 같다.
	bl_idname = "export.lue"

	# 아마 File 탭 중에서 Export 탭?
	bl_label = "Export"

	# 메뉴 탭에서 마우스를 올려놓고 있으면 보여주는 안내문구
	__doc__ = "Level Up Engine Exporter (.lue)"

	# 자동으로 untitled.{format}의 이름으로 디폴트 이름이 된다.
	filename_ext = ".lue"

	# Filter 옵션 관련 설정
	filter_glob : StringProperty( default = "*.lue", options = { 'HIDDEN' } )

	# 이게 블렌더에서 뭘 나타내는지 잘 모르겠음
	filepath : StringProperty(
		name = "File Path",
		description = "File path used for exporting the LUE file",
		maxlen = 1024,
		default = ""
		)

	# 이 부분이 우측에 Export 옵션들의 테두리를 만드는 함수
	def draw( self, context ):
		layout = self.layout

		box = layout.box()
		# 테두리 내부 리스트 예시
		# box.label( text = 'Essentials:' )
		# box.prop( self, 'option_triangulate' )
		# 이것을 하기 위해서는 위쪽에 BoolProperty가 선언되어 있어야 할 것으로 생각된다.
		# option_triangulate : BoolProperty( name = 777"Triangulate", description = "Triangulate all~", default = True )

	# 아마 선택된 객체와 카메라를 받아서 Export할 객체를 가져오는 함수인 것으로 생각됨
	# 그래서 선택되거나 카메라가 있어야 ok가 True가 되도록 할 것으로 예상
	@classmethod
	def poll( cls, context ):
		active = context.active_object
		selected = context.selected_objects
		camera = context.scene.camera
		ok = selected or camera
		return ok

	# 여기서 정리된 데이터를 파일에 입력하는 것 같다
	def writeLUE( self, filename, data):
		try:
			file = open( filename, 'w' )
		except IOError:
			print( 'Error : The file could not be written to. Aborting.' )
		else:
			file.write( data )
			file.close()

	# File View에서 파일 이름과 옵션을 모두 정하고 Export 버튼을 눌렀을 때 동작하는 함수
	def execute( self, context ):

		# 시간 측정을 위해 함수로 아마도? 현재 시각을 받아올 것
		# Export하기 위해 꼭 필요한 부분은 아니다.
		start = time.time()

		print( 'LUE Export Started.')

		# Python에서 Global 전역 변수를 사용하기 위해 블럭 내에서 다시
		# global {variable name}을 선언해주어야 한다.
		# 선언하지 않아도 사용은 가능하지만 해당 전역 변수의 값을 바꾸어도
		# 블록 내에서만 바뀐 값으로 사용된다.
		
		# 예시
		# global optionScale

		# Scene Export
		print( "Scene Exporting..." )
		print( "Selected Object Count : " + len( bpy.context.selected_objects ) )

		'''
		클래스를 통해 위쪽에 구현 예정
		'''

		print( "Scene Export Complete" )

		# 이 리턴 값은 Blender에 고지하는 용으로 사용하는 것일 듯
		return {'FINISHED'}

def menu_func( self, context ):
	self.layout.operator( ExportLUE.bl_idname, text = "Test Menu (.lue)")

def register():
	bpy.utils.register_class( ExportLUE )
	bpy.types.TOPBAR_MT_file_export.append( menu_func ) # register 부분과 관계 없이 메뉴를 만들어 줌

def unregister():
	bpy.utils.unregister_class( ExportLUE )
	bpy.types.TOPBAR_MT_file_export.remove( menu_func )

if __name__ == "__main__":
	register()