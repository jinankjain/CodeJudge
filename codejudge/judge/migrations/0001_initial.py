# -*- coding: utf-8 -*-
# Generated by Django 1.9 on 2016-04-04 16:57
from __future__ import unicode_literals

import ckeditor.fields
from django.conf import settings
import django.core.validators
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ('auth', '0007_alter_validators_add_error_messages'),
    ]

    operations = [
        migrations.CreateModel(
            name='Hacker',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('password', models.CharField(max_length=128, verbose_name='password')),
                ('last_login', models.DateTimeField(blank=True, null=True, verbose_name='last login')),
                ('is_superuser', models.BooleanField(default=False, help_text='Designates that this user has all permissions without explicitly assigning them.', verbose_name='superuser status')),
                ('username', models.CharField(max_length=20, unique=True, validators=[django.core.validators.RegexValidator(b'^[0-9a-zA-Z]*$', message=b'Only alphanumeric characters are allowed.')])),
                ('email', models.EmailField(max_length=255, unique=True, verbose_name=b'email address')),
                ('first_name', models.CharField(blank=True, max_length=30, null=True)),
                ('last_name', models.CharField(blank=True, max_length=50, null=True)),
                ('date_joined', models.DateTimeField(auto_now_add=True)),
                ('is_active', models.BooleanField(default=True)),
                ('is_staff', models.BooleanField(default=False)),
                ('profileImage', models.ImageField(upload_to=b'avatar')),
                ('groups', models.ManyToManyField(blank=True, help_text='The groups this user belongs to. A user will get all permissions granted to each of their groups.', related_name='user_set', related_query_name='user', to='auth.Group', verbose_name='groups')),
                ('user_permissions', models.ManyToManyField(blank=True, help_text='Specific permissions for this user.', related_name='user_set', related_query_name='user', to='auth.Permission', verbose_name='user permissions')),
            ],
            options={
                'abstract': False,
            },
        ),
        migrations.CreateModel(
            name='Comments',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('commentText', models.TextField()),
            ],
        ),
        migrations.CreateModel(
            name='Contest',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('contestName', models.CharField(max_length=200, unique=True)),
                ('startTime', models.DateTimeField()),
                ('endTime', models.DateTimeField()),
            ],
        ),
        migrations.CreateModel(
            name='Language',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('language', models.CharField(max_length=200)),
                ('extension', models.CharField(max_length=10)),
            ],
        ),
        migrations.CreateModel(
            name='Link',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('LinkUrl', models.CharField(max_length=200)),
                ('LinkDescription', models.CharField(max_length=200)),
            ],
        ),
        migrations.CreateModel(
            name='Notification',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('NotificationText', models.TextField()),
            ],
        ),
        migrations.CreateModel(
            name='Problem',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('problemSetter', models.CharField(max_length=200)),
                ('problemTitle', models.CharField(max_length=200)),
                ('problemStatement', ckeditor.fields.RichTextField()),
                ('testInput', models.FileField(upload_to=b'testInput')),
                ('testOutput', models.FileField(upload_to=b'testOutput')),
                ('timeLimit', models.PositiveSmallIntegerField()),
                ('languagesAllowed', models.CommaSeparatedIntegerField(max_length=200)),
                ('inputFormat', ckeditor.fields.RichTextField()),
                ('outputFormat', ckeditor.fields.RichTextField()),
                ('constraints', ckeditor.fields.RichTextField()),
                ('sampleInput', ckeditor.fields.RichTextField()),
                ('sampleOutput', ckeditor.fields.RichTextField()),
                ('solvedBy', models.PositiveSmallIntegerField(default=0)),
                ('contest', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='judge.Contest')),
            ],
        ),
        migrations.CreateModel(
            name='Solution',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('solution', models.FileField(upload_to=b'solution')),
                ('attempts', models.PositiveSmallIntegerField()),
                ('time', models.DecimalField(decimal_places=2, max_digits=2)),
                ('status', models.PositiveSmallIntegerField()),
                ('contest', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='judge.Contest')),
                ('hacker', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL)),
                ('language', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='judge.Language')),
                ('problem', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='judge.Problem')),
            ],
        ),
        migrations.AddField(
            model_name='comments',
            name='contest',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='judge.Contest'),
        ),
        migrations.AddField(
            model_name='comments',
            name='hacker',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='comments',
            name='problem',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='judge.Problem'),
        ),
    ]
