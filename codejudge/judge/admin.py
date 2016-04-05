from django.contrib import admin
from judge.models import *

# Register your models here.
admin.site.register(Hacker)
admin.site.register(Problem)
admin.site.register(Contest)
admin.site.register(Language)
admin.site.register(Solution)
admin.site.register(Link)
admin.site.register(Notification)