from django.conf.urls import *
from django.contrib import admin
from django.conf.urls.static import static
from django.conf import settings

admin.site.site_header = 'CodeJudge-IIT Jodhpur Admin'

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'codejudge.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', admin.site.urls),
    url(r'^judge/', include('judge.urls', namespace="judge")),
    url(r'^ckeditor/', include('ckeditor_uploader.urls')),
    url(r'^v1/', include('v1.urls')),

)+ static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT) 
